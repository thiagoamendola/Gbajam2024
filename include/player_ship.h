#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"

#include "colliders.h"
#include "controller.h"
#include "player_laser.h"
#include "enemy_manager.h"

// - Constants

namespace fr::model_3d_items
{

constexpr inline bn::color hurt_colors[] = {
    bn::color(18, 0, 0),
    bn::color(18, 0, 0),
};

constexpr const sphere_collider ship_colliders[] = {
    // sphere_collider(fr::point_3d(-15, 0, 7), 4),
    // sphere_collider(fr::point_3d(15, 0, 7), 4),
    // sphere_collider(fr::point_3d(-15, 0, -7), 4),
    // sphere_collider(fr::point_3d(15, 0, -7), 4),
    sphere_collider(fr::point_3d(0, 0, 0), 8)
    
};

constexpr size_t ship_colliders_count = sizeof(ship_colliders) / sizeof(ship_colliders[0]);

} // namespace fr::model_3d_items

// - Main class

class player_ship
{
  public:
    player_ship(controller *controller, fr::camera_3d *camera,
                fr::models_3d *models);

    void destroy();

    void update();

    void collision_update(const fr::model_3d_item **static_model_items, size_t static_items_count,
      enemy_manager enemies);

    int statics_render(const fr::model_3d_item **static_model_items,
                       int static_count);

    fr::model_3d *get_model()
    {
        return _model;
    };

    fr::point_3d get_position() const
    {
        return _model->position();
    }

    int get_health() const
    {
        return health;
    }

    void set_target_position(const bn::point target_pos)
    {
        target_position.set_x(target_pos.x());
        target_position.set_y(target_pos.y());
    }

    // - Movement
    const bn::fixed MANEUVER_SPEED = 3;
    const bn::fixed FORWARD_SPEED = 2.5;
    const bn::fixed YAW_MAX = 4000;
    const bn::fixed PITCH_MAX = 4000;

    // - Cooldowns
    const int DAMAGE_COOLDOWN = 60; // 1 second

  private:
    controller *_controller;
    fr::camera_3d *_camera;

    fr::models_3d *_models;
    fr::model_3d *_model;
    fr::model_3d *_test;

    player_laser _player_laser;

    sphere_collider_set<fr::model_3d_items::ship_colliders_count>
        _sphere_collider_set;

    int health = 3;
    int damage_cooldown = 0;
    bn::point target_position;
};

#endif
