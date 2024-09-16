
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
#include "scene_type.h"
#include "test_3d_scene.h"
#include "test_3d_scene_statics.h"

#include "bn_sprite_items_butano_background_2.h"
#include "bn_sprite_items_ninja.h"
#include "models/shot.h"

test_3d_scene::test_3d_scene()
    : _player_ship(&_controller, &_camera, &_models), _prepare_to_leave(false)
//   _test_sprite_sprite_3d_item(bn::sprite_items::butano_background_2, 0)
{
    // Stage stup
    _camera.set_position(fr::point_3d(0, 1040, 0));
    _models.load_colors(scene_colors, get_scene_color_mapping());

    bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));

    // Set music
    // bn::music_items::gameplay.play(1);

    // Test sprite 3D
    // _test_sprite = &_models.create_sprite(_test_sprite_sprite_3d_item);
    // _test_sprite->set_position(fr::point_3d(0, 760, -20));
    // _test_sprite->set_theta(32000);
}

// <-- ADD THIS TO HEADER???
void render_models(fr::camera_3d &_camera, fr::models_3d &_models,
                   const fr::model_3d_item **_static_model_items,
                   bn::span<const fr::model_3d_item> &_model_items)
{
    // - Create stage_section_renderer
    // - it should have a render_section(section) with the imediate code
    // below
    // - later, make it start rendering only if camera is below starting_pos
    // - Make it stop rendering if camera is below ending_pos
    // - Create another section so we can test some more partial renders
    // - For now, iterate through all sections in list. We can do something
    // smarter later.

    // fr::point_3d camera_pos = _camera->position();
    // camera_pos.set_y(camera_pos.y() - FORWARD_SPEED);
    // _camera->set_position(camera_pos);

    const bn::fixed camera_position = _camera.position().y();
    // BN_LOG("CAMERA POS: " + bn::to_string<32>(camera_position));

    // render section
    const int static_model_count = section_1.static_model_count();
    BN_LOG("STATICS SIZE: " + bn::to_string<32>(static_model_count));

    // <-- If new section has less models, we might run into an issue
    for (int i = 0; i < static_model_count; i++)
    {
        _static_model_items[i] = &section_1.static_model_items()[i];
    }

    _models.set_static_model_items(_static_model_items, static_model_count);

    // Final models update
    _models.update(_camera);
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

    // <-- I should separate this into my own rendering selection method
    // <-- Can I change it to span?
    {
        render_models(_camera, _models, _static_model_items, _model_items);
    }

    // <-- IMPLEMENT COLLISION
    // BN_LOG(collision_detection::is_colliding_with_static(
    //     _player_ship.get_model(), _model_items));

    return result;
}
