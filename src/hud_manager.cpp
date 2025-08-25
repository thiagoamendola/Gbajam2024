#include "hud_manager.h"

#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_log.h"
#include "bn_math.h"

#include "fr_camera_3d.h"
#include "fr_point_3d.h"

#include "controller.h"
#include "player_ship.h"

#include "bn_sprite_items_target_ui.h"
#include "common_variable_8x16_sprite_font.h"

hud_manager::hud_manager(controller *controller, fr::camera_3d *camera, player_ship *player_ship)
    : _controller(controller), _camera(camera), _player_ship(player_ship),
      _text_generator(common::variable_8x16_sprite_font), _target_spr(bn::sprite_items::target_ui.create_sprite(0, 0)),
      _target_growth_action()
{
    // Setup target sprite
    _target_spr.set_horizontal_scale(1.2);
    _target_spr.set_vertical_scale(1.2);
    _target_growth_action = bn::sprite_scale_loop_action(_target_spr, 15, 2.0);
}

void hud_manager::destroy()
{
    _target_growth_action.reset();
}

void hud_manager::update()
{
    // Clear texts.
    _text_sprites.clear();

    // text generators should be created only once // <-- what to do with this?

    // Display location Y debug text.
    if (_controller->is_debug_text_enabled())
    {
        _text_generator.generate(-7 * 16, -72, "Location (Y): " + bn::to_string<64>(int(_camera->position().y())),
                                 _text_sprites);
    }
    else
    {
        _text_generator.generate(-7 * 16, -72, "HEALTH: " + bn::to_string<64>(_player_ship->get_health()),
                                 _text_sprites);
    }

    _move_target();
}

void hud_manager::statics_update(int static_count)
{
    // Display static count debug text.
    if (_controller->is_debug_text_enabled())
    {
        _text_generator.generate(-7 * 16, -60, "Static Objs: " + bn::to_string<64>(static_count), _text_sprites);
    }
}

void hud_manager::_move_target()
{
    // Get raw input vector
    bn::fixed_point dir_input = _controller->get_smooth_directional();

    BN_LOG("[target] dir_input: " + bn::to_string<64>(dir_input.x()) + ", " + bn::to_string<64>(dir_input.y()));

    bn::point target_pos;

    if (bn::abs(dir_input.x()) < 0.15 && bn::abs(dir_input.y()) < 0.15)
    {
        target_pos = _compute_target_return();
    }
    else
    {
        target_pos = _compute_target_move(dir_input);
    }

    _target_spr.set_y(target_pos.y());
    _target_spr.set_x(target_pos.x());

    _player_ship->set_target_position(target_pos);

    _target_growth_action->update();
}

bn::point hud_manager::_compute_target_return()
{
    // Return to center of ship.
    constexpr int focal_length_shift = fr::constants_3d::focal_length_shift;
    fr::point_3d target_world_pos = _player_ship->get_position();
    fr::point_3d cam_pos = _camera->position();
    fr::point_3d cam_u = _camera->u();
    fr::point_3d cam_v = _camera->v();
    bn::fixed depth_position = target_world_pos.y() - 200; // Setup distance in front of ship
    bn::fixed depth_to_camera = _camera->position().y() - depth_position;

    int cam_x_i = cam_pos.x().integer();
    int cam_z_i = cam_pos.z().integer();
    int world_x_i = target_world_pos.x().integer();
    int world_z_i = target_world_pos.z().integer();
    int depth_to_camera_i = depth_to_camera.integer();

    // Reconstruct dir_x and dir_z (integer approximation):
    int dir_x_i = cam_x_i + ((world_x_i << focal_length_shift) / depth_to_camera_i);
    int dir_z_i = cam_z_i - ((world_z_i << focal_length_shift) / depth_to_camera_i);

    // Solve 2x2 linear system:
    int ux_i = cam_u.x().integer();
    int vx_i = cam_v.x().integer();
    int uz_i = cam_u.z().integer();
    int vz_i = cam_v.z().integer();
    int det = ux_i * vz_i - vx_i * uz_i;

    int sx_i = 0;
    int sy_i = 0;
    if(det != 0)
    {
        sx_i = (dir_x_i * vz_i - vx_i * dir_z_i) / det; // <-- OPTIMIZE: REPLACE DIVISION
        sy_i = (ux_i * dir_z_i - dir_x_i * uz_i) / det; // <-- OPTIMIZE: REPLACE DIVISION
    }

    bn::point rest_pos {int16_t(sx_i), int16_t(sy_i)};

    // Move towards rest_pos gradually, capped per axis to avoid overshoot.
    const int TARGET_SPEED = 10; // same speed constant used in caller
    int cur_x = _target_spr.x().integer();
    int cur_y = _target_spr.y().integer();
    int dx = rest_pos.x() - cur_x;
    int dy = rest_pos.y() - cur_y;

    if(dx > 0)
    {
        cur_x += (dx > TARGET_SPEED) ? TARGET_SPEED : dx;
    }
    else if(dx < 0)
    {
        int adx = -dx;
        cur_x -= (adx > TARGET_SPEED) ? TARGET_SPEED : adx;
    }

    if(dy > 0)
    {
        cur_y += (dy > TARGET_SPEED) ? TARGET_SPEED : dy;
    }
    else if(dy < 0)
    {
        int ady = -dy;
        cur_y -= (ady > TARGET_SPEED) ? TARGET_SPEED : ady;
    }

    return bn::point(cur_x, cur_y);
}

bn::point hud_manager::_compute_target_move(const bn::fixed_point& dir_input)
{
    // Move target sprite based on input.
    constexpr int TARGET_SPEED = 10; // <-- Magic number
    bn::point target_pos;
    target_pos.set_x(int(_target_spr.x() + dir_input.x() * TARGET_SPEED)); // StarFox 64 multiplies this during barrel roll
    target_pos.set_y(int(_target_spr.y() + dir_input.y() * TARGET_SPEED));

    // Clamp to screen bounds.
    if (target_pos.x() < -110)
    {
        target_pos.set_x(-110);
    }
    else if (target_pos.x() > 110)
    {
        target_pos.set_x(110);
    }
    if (target_pos.y() < -75)
    {
        target_pos.set_y(-75);
    }
    else if (target_pos.y() > 75)
    {
        target_pos.set_y(75);
    }

    return target_pos;
}
