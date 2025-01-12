#include "test_3d_scene.h"
#include "test_3d_scene_statics.h"

#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_string.h"

#include "fr_model_3d_item.h"
#include "fr_model_colors.h"

#include "collision_detection.h"
#include "player_laser.h"
#include "scene_type.h"
#include "stage_section_renderer.h"

#include "bn_sprite_items_butano_background_2.h"
#include "bn_sprite_items_ninja.h"
#include "models/shot.h"

#include "bn_regular_bg_items_floor.h"
#include "bn_regular_bg_items_moon.h"
#include "bn_regular_bg_ptr.h"

test_3d_scene::test_3d_scene()
    : _player_ship(&_controller, &_camera, &_models), _prepare_to_leave(false),
      _scene_bg(bn::regular_bg_items::floor.create_bg(0, 0))
//   _moon_bg(bn::regular_bg_items::moon.create_bg(0, 20))
//   _test_sprite_sprite_3d_item(bn::sprite_items::butano_background_2, 0)
{
    // Stage setup
    _camera.set_position(fr::point_3d(0, 1040, 0));
    _models.load_colors(scene_colors, get_scene_color_mapping());

    bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));

    // Set music
    // bn::music_items::gameplay.play(1); // Very slow
    // bn::music_items::gameplay3.play(1); // Starts and breaks

    // Test sprite 3D
    // _test_sprite = &_models.create_sprite(_test_sprite_sprite_3d_item);
    // _test_sprite->set_position(fr::point_3d(0, 760, -20));
    // _test_sprite->set_theta(32000);
}

bn::optional<scene_type> test_3d_scene::update()
{
    bn::optional<scene_type> result;
    int static_count = 0; 

    if (_prepare_to_leave)
    {
        result = scene_type::BUTANO_INTRO;
    }
    else if (bn::keypad::start_pressed())
    {
        _player_ship.destroy();
        _prepare_to_leave = true;
    }
    else
    {

        {
            // <-- Camera old randomness. Likely removable.

            fr::point_3d new_cam_pos = _camera.position();

            // if (bn::keypad::up_held())
            // {
            //     new_cam_pos.set_y(new_cam_pos.y() + 2); // Max is 1024
            // }
            // else if (bn::keypad::down_held())
            // {
            //     bn::fixed_t new_value = new_cam_pos.y() - 2;
            //     new_value = new_value > 2 ? new_value : 2;
            //     new_cam_pos.set_y(new_value);
            // }

            _camera.set_position(new_cam_pos);

            // BN_LOG(_camera.position().y());
        }

        // <-- might need to reorganize things here

        static_count = stage_section_renderer::manage_section_render(
            sections, sections_count, _camera, _models, _static_model_items);

        _player_ship.update(_static_model_items, static_count);
    }

    {
        // - Static object rendering
        // - Player Laser

        static_count =
            _player_ship.statics_render(_static_model_items, static_count);

        // Final models update
        // BN_LOG("STATIC MODEL COUNT: " + bn::to_string<32>(static_count));
        _models.set_static_model_items(_static_model_items, static_count);
        _models.update(_camera);
    }

    // <-- IMPLEMENT COLLISION
    // BN_LOG(collision_detection::is_colliding_with_static(
    //     _player_ship.get_model(), _model_items));

    return result;
}
