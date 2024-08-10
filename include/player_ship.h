#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "controller.h"
#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"

class player_ship
{
  public:
    player_ship(controller *controller, fr::camera_3d *camera,
                fr::models_3d *models);

    void update();

    void destroy();

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
};

#endif
