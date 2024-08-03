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
    _model->set_position(fr::point_3d(0, -80, 20));
    _model->set_phi(48000); // 270 degrees
}

void player_ship::update()
{
    bn::fixed_point dir_input = _controller->get_smooth_directional();

    bn::fixed SPEED = 3;

    fr::point_3d ship_pos = _model->position();
    ship_pos.set_x(ship_pos.x() + dir_input.x() * SPEED);
    ship_pos.set_z(ship_pos.z() + dir_input.y() * SPEED);
    _model->set_position(ship_pos);

    // bn::fixed old_phi = _model->phi();
    // // Remember to avoid Gymball lock with the following
    // _model->set_phi(0);
    // _model->set_psi(_model->psi() + 300);
    // _model->set_phi(old_phi + 1);
    BN_LOG("current: " + bn::to_string<32>(_model->phi()));
}

// <-- Should I put this in the destructor? Probaly not
void player_ship::destroy()
{
    _models->destroy_dynamic_model(*_model);
}
