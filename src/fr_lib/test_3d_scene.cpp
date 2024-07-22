
#include "test_3d_scene.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_colors.h"
#include "bn_fixed.h"
#include "bn_bg_palettes_actions.h"
#include "bn_log.h"

#include "scene_type.h"
#include "fr_model_colors.h"

// #include "models/fr_model_3d_items_gba.h"
// #include "models/fr_model_3d_items_butano.h"
// #include "models/fr_model_3d_items_bush.h"
// #include "models/cartoon_tree.h"
#include "models/shot.h"
// #include "models/test.h"

test_3d_scene::test_3d_scene() : prepare_to_leave(false)
{
    _camera.set_position(fr::point_3d(0, 40, 0));
    // _models.load_colors(fr::model_3d_items::gba_colors);
    // _models.load_colors(fr::model_3d_items::butano_colors);
    // _models.load_colors(fr::model_3d_items::test_colors);
    _models.load_colors(fr::model_3d_items::shot_colors);
    // _models.load_colors(fr::default_model_colors);

    _model = &_models.create_dynamic_model(fr::model_3d_items::shot_full);
    _model->set_position(fr::point_3d(0, -80, 0));

    for (int i = 0; i < 3; i++)
    {
        // _model = &_models.create_dynamic_model(fr::model_3d_items::gba);
        // _model = &_models.create_dynamic_model(fr::model_3d_items::butano);
        // _trees[i] = &_models.create_dynamic_model(fr::model_3d_items::cartoon_tree_full);
        // _model = &_models.create_dynamic_model(fr::model_3d_items::test_full);
        // _model = &_models.create_dynamic_model(fr::model_3d_items::bush);
        // _trees[i]->set_position(fr::point_3d(30 + i k* 35, 0 + i * 75, 0));
        // _model->set_psi(900);
    }

    bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));
}

bn::optional<scene_type> test_3d_scene::update()
{
    bn::optional<scene_type> result;

    if (prepare_to_leave)
    {
        result = scene_type::BUTANO_INTRO;
    }
    else if (bn::keypad::start_pressed())
    {
        _models.destroy_dynamic_model(*_model);
        prepare_to_leave = true;
    }
    else
    {
        fr::point_3d new_cam_pos = _camera.position();

        if (bn::keypad::up_held())
        {
            new_cam_pos.set_y(new_cam_pos.y() + 2); // Max is 1024
        }
        else if (bn::keypad::down_held())
        {
            bn::fixed_t new_value = new_cam_pos.y() - 2;
            new_value = new_value > 2 ? new_value : 2;
            new_cam_pos.set_y(new_value);
        }

        _camera.set_position(new_cam_pos);

        BN_LOG(_camera.position().y());

        bn::fixed old_phi = _model->phi();
        _model->set_phi(0);
        _model->set_psi(_model->psi() + 300);
        _model->set_phi(old_phi + 100);
        // _model->set_theta(_model->theta() + 300);
    }

    _models.update(_camera);

    return result;
}
