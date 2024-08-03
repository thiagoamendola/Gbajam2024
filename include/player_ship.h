#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

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

  private:
    controller *_controller;
    fr::camera_3d *_camera;

    fr::models_3d *_models;
    fr::model_3d *_model;
};

#endif
