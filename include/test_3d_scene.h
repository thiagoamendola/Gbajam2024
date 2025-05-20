#ifndef TEST_3D_SCENE_H
#define TEST_3D_SCENE_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_actions.h"

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "fr_scene.h"
// #include "fr_sprite_3d.h"
// #include "fr_sprite_3d_item.h"

#include "common_game_scene.h"
#include "controller.h"
#include "player_ship.h"
#include "ui_manager.h"
#include "enemy_manager.h"
#include "scene_type.h"

class test_3d_scene : public fr::scene
{

  public:
    test_3d_scene();

    [[nodiscard]] bn::optional<scene_type> update() final;

  private:

    common_game_scene _common_game_scene;

    // fr::model_3d *_model; // <-- RETURN FOR TEST

    bool _prepare_to_leave;

    // <-- 3D SPRITE TEST. REMOVE
    // fr::sprite_3d *_test_sprite = nullptr;
    // fr::sprite_3d_item _test_sprite_sprite_3d_item;
    
    // TEST SPRITE // <-- REMOVE
    // Target animated sprite
    bn::sprite_ptr _target_spr;
    // bn::sprite_animate_action<4> _target_action;
    bn::optional<bn::sprite_scale_loop_action> _target_growth_action;

    // Background
    // bn::regular_bg_ptr _scene_bg;
    bn::regular_bg_ptr _anim_bg;
    bn::regular_bg_cached_animate_action<5> _anim_bg_action;
    // bn::regular_bg_ptr _moon_bg;

};

#endif
