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
#include "bn_regular_bg_ptr.h"

test_3d_scene::test_3d_scene()
    : _player_ship(&_controller, &_camera, &_models), _prepare_to_leave(false),
      _scene_bg(bn::regular_bg_items::floor.create_bg(0, 0))
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

        _player_ship.update();
    }

    {
        // - Static object rendering

        int static_count = stage_section_renderer::manage_section_render(
            sections, sections_count, _camera, _models, _static_model_items);

        // - Player Laser

        // static_count = player_laser::handle_player_laser(
        //     &_player_ship, _static_model_items, static_count);

        // I need the model_3d_item instantiated at the time of models.update
        if (bn::keypad::a_held())
        {
            fr::vertex_3d laser_vertices[] = {
                fr::vertex_3d(_player_ship.get_model()->position() +
                              fr::point_3d(10, 0, 0)),
                fr::vertex_3d(_player_ship.get_model()->position() +
                              fr::point_3d(-10, 0, 0)),
                fr::vertex_3d(0, _player_ship.get_model()->position().y(), 0),
            };

            fr::face_3d laser_faces[] = {
                fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 1, 2, 0,
                            7),
                fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 2, 1, 0,
                            0),
            };

            bn::color laser_colors[] = {
                bn::color(24, 0, 0),
            };

            fr::model_3d_item laser_full(laser_vertices, laser_faces,
                                         laser_colors);

            if (static_count >= fr::constants_3d::max_static_models)
            {
                BN_LOG("Stage Section Renderer: reached static model max "
                       "limit: " +
                       bn::to_string<64>(fr::constants_3d::max_static_models));
            }
            else
            {
                _static_model_items[static_count] = &laser_full;
                static_count += 1;
            }
        }

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
