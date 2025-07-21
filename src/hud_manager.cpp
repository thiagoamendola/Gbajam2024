#include "hud_manager.h"

#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_log.h"

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

    const int TARGET_SPEED = 10;

    // BN_LOG("[target] dir_input: " + bn::to_string<64>(dir_input.x()) + ", " + bn::to_string<64>(dir_input.y()));

    bn::point target_pos;

    // if (dir_input.x() == 0 && dir_input.y() == 0)
    // {
    //     // Return to center of ship.
    //     fr::point_3d ship_pos = _player_ship->get_position();
    //     ship_pos.set_y(ship_pos.y() - 200); // Add some distance in front of ship for rest position.
    //     // Now I need to find a way to project that point to 2D screen coordinates.

    // }
    // else
    {
        // Move target sprite based on input.
        target_pos.set_x(int(_target_spr.x() + dir_input.x() * TARGET_SPEED));
        target_pos.set_y(int(_target_spr.y() + dir_input.y() * TARGET_SPEED));

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
    }

    _target_spr.set_y(target_pos.y());
    _target_spr.set_x(target_pos.x());

    _player_ship->set_target_position(target_pos);

    _target_growth_action->update();
}
