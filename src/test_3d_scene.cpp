
#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"

#include "collision_detection.h"
#include "fr_model_3d_item.h"
#include "fr_model_colors.h"
#include "scene_type.h"
#include "test_3d_scene.h"
#include "test_3d_scene_statics.h"

#include "models/shot.h"

test_3d_scene::test_3d_scene()
    : _model_items(static_model_items),
      _player_ship(&_controller, &_camera, &_models), _prepare_to_leave(false)
{
    // Stage stup
    _camera.set_position(fr::point_3d(0, 1040, 0));
    _models.load_colors(scene_colors, get_scene_color_mapping());

    bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));
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
    const int static_models_count = ARRAY_SIZE(static_model_items);

    for (int i = 0; i < static_models_count; i++)
    {
        _static_model_items[i] = &_model_items[i];
    }

    _models.set_static_model_items(_static_model_items, static_models_count);
    _models.update(_camera);

    BN_LOG(collision_detection::is_colliding_with_static(
        _player_ship.get_model(), _model_items));

    return result;
}
