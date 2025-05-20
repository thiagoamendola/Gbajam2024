#include "test_3d_scene.h"
#include "test_3d_scene_defs.h"

#include "bn_bg_palettes_actions.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_actions.h"

#include "fr_model_3d_item.h"
#include "fr_model_colors.h"

#include "collision_detection.h"
#include "scene_type.h"
#include "common_game_scene.h"

// #include "bn_sprite_items_butano_background_2.h"
// #include "bn_sprite_items_ninja.h"
#include "bn_sprite_items_target_ui.h"
#include "models/shot.h"

#include "bn_regular_bg_items_floor.h"
// #include "bn_regular_bg_items_moon.h"
#include "bn_regular_bg_items_bg_anim.h"
#include "bn_regular_bg_ptr.h"

test_3d_scene::test_3d_scene()
    : _common_game_scene(scene_colors, get_scene_color_mapping(), sections, sections_count),
    //   _player_ship(&_controller, &_camera, &_models),
    //   _enemy_manager(&_models, &_controller),
    //   _ui_manager(&_controller, &_camera),
      _prepare_to_leave(false),
      _target_spr(bn::sprite_items::target_ui.create_sprite(0, 0)),
      _target_growth_action(),
    //   _ninja_action(bn::create_sprite_animate_action_forever(
    //       _ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 0, 1, 2, 3)),
      _anim_bg(bn::regular_bg_items::bg_anim.create_bg(0, 0)),
      _anim_bg_action(bn::create_regular_bg_cached_animate_action_forever(
            _anim_bg, 6, bn::regular_bg_items::bg_anim.map_item(), 0, 1, 2, 3))
    //   _scene_bg(bn::regular_bg_items::floor.create_bg(0, 0)),
//   _moon_bg(bn::regular_bg_items::moon.create_bg(0, 20))
//   _test_sprite_sprite_3d_item(bn::sprite_items::butano_background_2, 0)
{

    // Scenario setup
    // bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));

    // Set music
    // bn::music_items::gameplay.play(1); // Very slow
    // bn::music_items::gameplay3.play(1); // Starts and breaks

    // Test sprite 3D
    // _test_sprite = &_models.create_sprite(_test_sprite_sprite_3d_item);
    // _test_sprite->set_position(fr::point_3d(0, 760, -20));
    // _test_sprite->set_theta(32000);

    // Setup target sprite
    _target_spr.set_horizontal_scale(1.2);
    _target_spr.set_vertical_scale(1.2);
    _target_growth_action = bn::sprite_scale_loop_action(
        _target_spr, 15, 2.0);
}

bn::optional<scene_type> test_3d_scene::update()
{
    bn::optional<scene_type> result;

    // <-- move
    _anim_bg_action.update();

    bool change_scene = _common_game_scene.update();
    
    if (change_scene)
    {
        _target_growth_action.reset();

        result = scene_type::BUTANO_INTRO;
        return result;
    }

    {
        // <-- REMOVE LATER
        // TARGET CODE
        // Get raw input vector
        bn::fixed_point dir_input = _common_game_scene.get_controller()->get_smooth_directional();

        _target_spr.set_y(_target_spr.y() + dir_input.y() * 10);
        _target_spr.set_x(_target_spr.x() + dir_input.x() * 10);

        _target_growth_action->update();
    }

    return result;
}

// <-- Make Destroy
