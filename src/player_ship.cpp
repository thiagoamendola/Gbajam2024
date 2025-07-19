#include "player_ship.h"

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_sound_items.h"
#include "bn_string.h"

#include "fr_point_3d.h"
#include "fr_constants_3d.h"

#include "enemy_manager.h"
#include "controller.h"

#include "models/shot.h"
// #include "models/player_ship_01.h"
#include "models/player_ship_02.h"

player_ship::player_ship(controller *controller, fr::camera_3d *camera,
                         fr::models_3d *models)
    : _controller(controller), _camera(camera), _models(models),
      _sphere_collider_set(fr::model_3d_items::ship_colliders)
{
    _model =
        &_models->create_dynamic_model(fr::model_3d_items::player_ship_02_full);
    // x, y (back/forward), z (down/up)
    _model->set_position(fr::point_3d(0, 860, 0));
    _model->set_psi(16383); // 90 degrees
}

void player_ship::destroy()
{
    _models->destroy_dynamic_model(*_model);
}

void player_ship::update()
{
    bn::fixed_point dir_input = _controller->get_smooth_directional();

    {
        // - Player ship movement

        fr::point_3d ship_pos = _model->position();

        // Directional movement

        ship_pos.set_x(ship_pos.x() + dir_input.x() * MANEUVER_SPEED);
        ship_pos.set_z(ship_pos.z() + dir_input.y() * MANEUVER_SPEED);

        if (ship_pos.x() < -65)
        {
            ship_pos.set_x(-65);
        }
        else if (ship_pos.x() > 65)
        {
            ship_pos.set_x(65);
        }
        if (ship_pos.z() < -45)
        {
            ship_pos.set_z(-45);
        }
        else if (ship_pos.z() > 45)
        {
            ship_pos.set_z(45);
        }

        BN_LOG("[player_ship] position: " + bn::to_string<64>(ship_pos.x()) + ", " + bn::to_string<64>(ship_pos.z()));

        // Forward movement
        ship_pos.set_y(ship_pos.y() - FORWARD_SPEED);

        _model->set_position(ship_pos);
    }

    {
        // - Player ship Yaw/Pitch

        _model->set_phi(YAW_MAX * dir_input.x());
        _model->set_psi(16383 + -PITCH_MAX * dir_input.y());
    }

    {
        // - Camera movement

        fr::point_3d camera_pos = _camera->position();
        camera_pos.set_y(camera_pos.y() - FORWARD_SPEED);
        _camera->set_position(camera_pos);
    }

    {
        // - Player Laser
        _player_laser.handle_player_laser();
    }

    {
        // - Sound test // <-- Remove later
        // if (bn::keypad::b_pressed())
        // {
        //     bn::sound_items::player_damage.play();
        // }
        // else if (bn::keypad::r_pressed())
        // {
        //     bn::sound_items::player_death.play();
        // }
        // else if (bn::keypad::l_pressed())
        // {
        //     bn::sound_items::enemy_death.play();
        // }
    }

    {
        // Update general controller input.
        _controller->update();

        // Update colliders.
        _sphere_collider_set.set_origin(get_model()->position());
    }
}

void player_ship::collision_update(const fr::model_3d_item **static_model_items,
    size_t static_items_count, enemy_manager enemies)
{
    {
        if (damage_cooldown > 0)
        {
            damage_cooldown--;
            // Blink ship
            if (damage_cooldown % 6 < 3) {
                _model->set_palette(fr::model_3d_items::hurt_colors);
            } else {
                _model->set_palette(fr::model_3d_items::player_ship_02_colors);
            }
            return;
        }

        // - Collision with statics
        if (_sphere_collider_set.colliding_with_statics(static_model_items, static_items_count))
        {
            _model->set_palette(fr::model_3d_items::hurt_colors);
            bn::sound_items::player_damage.play();
            damage_cooldown = DAMAGE_COOLDOWN;
            health--;
            return;
        }
        // - Collision with dynamics
        else if (_sphere_collider_set.colliding_with_dynamic(enemies._asteroid.get_collider())) // <-- Improve
        {
            _model->set_palette(fr::model_3d_items::hurt_colors);
            bn::sound_items::player_damage.play();
            damage_cooldown = DAMAGE_COOLDOWN;
            health--;
        }
        else
        {
            _model->set_palette(fr::model_3d_items::player_ship_02_colors);
        }
    }

}

int player_ship::statics_render(const fr::model_3d_item **static_model_items,
                                int static_count)
{
#if LOG_STATIC_RENDER_STEPS
    BN_LOG("[statics_render] Initial value: " +
           bn::to_string<64>(static_count));
#endif

    // Render laser model
    int current_static_count = _player_laser.render_player_laser(
        get_model()->position(), _model->psi(), _model->phi(),
        static_model_items, static_count);

#if LOG_STATIC_RENDER_STEPS
    BN_LOG("[statics_render] Updated laser: " +
           bn::to_string<64>(current_static_count));
#endif

    // Render debug collider models
    if (_controller->is_collider_display_enabled())
    {
        current_static_count = _sphere_collider_set.debug_collider(
            static_model_items, current_static_count);
    }

#if LOG_STATIC_RENDER_STEPS
    BN_LOG("[statics_render] Updated debug collider: " +
           bn::to_string<64>(current_static_count));
#endif

    return current_static_count;
}