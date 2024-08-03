
#include "test_3d_scene.h"

#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"

#include "fr_model_3d_item.h"
#include "fr_model_colors.h"
#include "fr_transformed_model_3d_item.h"
#include "scene_type.h"
#include "static_model_3d_item.h"

#include "models/bush.h"
#include "models/shot.h"

constexpr auto _bush_model = static_model_3d_item<fr::model_3d_items::bush_full>(fr::point_3d(20, 0, 40), 100);
constexpr auto _bush_model_2 = static_model_3d_item<fr::model_3d_items::bush_full>(fr::point_3d(0, 30, 40), 1000);
constexpr auto _bush_model_3 = static_model_3d_item<fr::model_3d_items::bush_full>(fr::point_3d(-30, -90, 40), 10000);

constexpr fr::model_3d_item static_model_items[] = {
    _bush_model_3.item(),
    _bush_model_2.item(),
    _bush_model.item()};

test_3d_scene::test_3d_scene()
    : _model_items(static_model_items), _prepare_to_leave(false)
{
    _camera.set_position(fr::point_3d(0, 40, 0));
    _models.load_colors(fr::model_3d_items::shot_colors); // <-- The entire scene shares the same pallette. I'll have to do something about it
    // _models.load_colors(fr::model_3d_items::bush_colors);
    // _models.load_colors(fr::default_model_colors);

    _model = &_models.create_dynamic_model(fr::model_3d_items::shot_full);
    _model->set_position(fr::point_3d(0, -80, 20)); // x, y (back/forward), z (down/up)

    // _model2 = &_models.create_dynamic_model(fr::model_3d_items::shot_full);
    // _model2->set_position(fr::point_3d(0, -80, -20)); // x, y (back/forward), z (down/up)

    bn::bg_palettes::set_transparent_color(bn::color(25, 18, 25));

    BN_LOG("Constructor check list model. faces = ", _model_items[0].faces().size());
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
        _models.destroy_dynamic_model(*_model);
        _prepare_to_leave = true;
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
    }

    // <-- I should separate this into my own rendering selection method
    const int static_models_count = 3;
    const fr::model_3d_item *model_items_for_update = _model_items.data(); // <-- Could the error be here?

    for (int i = 0; i < static_models_count; i++)
    {
        _static_model_items[i] = &model_items_for_update[i];
    }

    _models.set_static_model_items(_static_model_items, static_models_count);
    _models.update(_camera);

    return result;
}
