#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_point_3d.h"

#include "player_ship.h"

#include "models/shot.h"

player_ship::player_ship(controller *controller, fr::camera_3d *camera,
                         fr::models_3d *models)
    : _controller(controller), _camera(camera), _models(models)
{
    _model = &_models->create_dynamic_model(fr::model_3d_items::shot_full);
    // x, y (back/forward), z (down/up)
    _model->set_position(fr::point_3d(0, 920, 20));
    _model->set_phi(48000); // 270 degrees
}

void player_ship::update()
{
    bn::fixed_point dir_input = _controller->get_smooth_directional();

    {
        fr::point_3d ship_pos = _model->position();

        // Player movement
        ship_pos.set_x(ship_pos.x() + dir_input.x() * MANEUVER_SPEED);
        ship_pos.set_z(ship_pos.z() + dir_input.y() * MANEUVER_SPEED);

        // Forward movement
        ship_pos.set_y(ship_pos.y() - FORWARD_SPEED);

        _model->set_position(ship_pos);
    }

    {
        fr::point_3d camera_pos = _camera->position();
        camera_pos.set_y(camera_pos.y() - FORWARD_SPEED);
        _camera->set_position(camera_pos);
        BN_LOG("CAMERA POS: " + bn::to_string<32>(camera_pos.y()));
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
