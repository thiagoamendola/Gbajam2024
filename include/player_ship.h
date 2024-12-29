#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"

#include "colliders.h"
#include "controller.h"
#include "player_laser.h"

// - Constants

namespace fr::model_3d_items
{

constexpr inline bn::color hurt_colors[] = {
    bn::color(18, 0, 0),
};

constexpr const sphere_collider ship_colliders[] = {
    sphere_collider(fr::point_3d(15, 0, 0), 7),
    sphere_collider(fr::point_3d(0, 0, 0), 7)
    
};

} // namespace fr::model_3d_items

// - Main class

class player_ship
{
  public:
    player_ship(controller *controller, fr::camera_3d *camera,
                fr::models_3d *models);

    void update();

    void destroy();

    int statics_render(const fr::model_3d_item **static_model_items,
                       int static_count);

    fr::model_3d *get_model()
    {
        return _model;
    };

    const bn::fixed MANEUVER_SPEED = 3;
    const bn::fixed FORWARD_SPEED = 2.5;

    const bn::fixed YAW_MAX = 4000;
    const bn::fixed PITCH_MAX = 4000;

  private:
    controller *_controller;
    fr::camera_3d *_camera;

    fr::models_3d *_models;
    fr::model_3d *_model;

    player_laser _player_laser;

    // <-- Make it a constant
    sphere_collider_set _sphere_collider_set;

    bool enable_collider_display = false;
};

#endif
