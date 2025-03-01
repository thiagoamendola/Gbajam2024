#ifndef TEST_3D_SCENE_H
#define TEST_3D_SCENE_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "fr_scene.h"
// #include "fr_sprite_3d.h"
// #include "fr_sprite_3d_item.h"

#include "controller.h"
#include "player_ship.h"
#include "enemy_manager.h"
#include "scene_type.h"

class test_3d_scene : public fr::scene
{

  public:
    test_3d_scene();

    [[nodiscard]] bn::optional<scene_type> update() final;

  private:
    controller _controller;

    fr::camera_3d _camera;
    fr::models_3d _models;

    player_ship _player_ship;

    enemy_manager _enemy_manager;

    fr::model_3d *_model;

    bn::span<const fr::model_3d_item> _model_items; // <-- CAN BEW REMOVED NOW
    const fr::model_3d_item
        *_static_model_items[fr::constants_3d::max_static_models];

    bool _prepare_to_leave;

    // <-- 3D SPRITE TEST. REMOVE
    // fr::sprite_3d *_test_sprite = nullptr;
    // fr::sprite_3d_item _test_sprite_sprite_3d_item;

    // Background
    // bn::regular_bg_ptr _scene_bg;
    bn::regular_bg_ptr _anim_bg;
    bn::regular_bg_cached_animate_action<5> _anim_bg_action;
    // bn::regular_bg_ptr _moon_bg;

    // UI
    bn::sprite_text_generator _text_generator; // <-- move to common stuff
    bn::vector<bn::sprite_ptr, 32> _text_sprites;

};

#endif
