#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_sound_items.h"
#include "bn_string.h"

#include "fr_point_3d.h"

#include "player_ship.h"

#include "models/shot.h"
// #include "models/player_ship_01.h"
#include "models/player_ship_02.h"

player_ship::player_ship(controller *controller, fr::camera_3d *camera,
                         fr::models_3d *models)
    : _controller(controller), _camera(camera), _models(models)
{
    _model =
        &_models->create_dynamic_model(fr::model_3d_items::player_ship_02_full);
    // x, y (back/forward), z (down/up)
    _model->set_position(fr::point_3d(0, 860, 20));
    _model->set_psi(16383); // 90 degrees
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
        if (bn::keypad::b_pressed())
        {
            bn::sound_items::player_damage.play();
        }
        else if (bn::keypad::r_pressed())
        {
            bn::sound_items::player_death.play();
        }
        else if (bn::keypad::l_pressed())
        {
            bn::sound_items::enemy_death.play();
        }
    }

    {
        // - Test collision
        if (bn::keypad::b_held())
        {
            _model->set_palette(fr::model_3d_items::hurt_colors);
        }
        else
        {
            _model->set_palette(fr::model_3d_items::player_ship_02_colors);
        }
    }

    // bn::fixed old_phi = _model->phi();
    // // Remember to avoid Gymball lock with the following
    // _model->set_phi(0);
    // _model->set_psi(_model->psi() + 300);
    // _model->set_phi(old_phi + 1);
}

// <-- Should I put this in the destructor? Probaly not
void player_ship::destroy()
{
    _models->destroy_dynamic_model(*_model);
}

int player_ship::statics_render(const fr::model_3d_item **static_model_items,
                                int static_count)
{
    // Handle laser static model
    return _player_laser.render_player_laser(get_model()->position(),
                                             _model->psi(), _model->phi(),
                                             static_model_items, static_count);
}