
#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_sprite_text_generator.h"
#include "common_variable_8x16_sprite_font.h"

#include "fr_model_3d_item.h"
#include "fr_model_colors.h"

#include "scene_type.h"
#include "test_3d_scene_statics.h"
#include "title_scene.h"

#include "models/player_ship_02.h"
#include "models/shot.h"

title_scene::title_scene() : _prepare_to_leave(false)
{
    _camera.set_position(fr::point_3d(0, 0, 0));
    _camera.set_phi(6000);

    _models.load_colors(fr::model_3d_items::player_ship_02_colors);

    _model =
        &_models.create_dynamic_model(fr::model_3d_items::player_ship_02_full);
    _model->set_position(
        fr::point_3d(15, -110, 10)); // x, y (back/forward), z (down/up)

    // 16000 => 90 degrees
    // _model->set_psi(58000);
    _model->set_phi(16000);

    bn::bg_palettes::set_transparent_color(bn::color(2, 2, 6));

    // Set text
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.generate(-100, 58, "Press Start", _text_sprites);
}

bn::optional<scene_type> title_scene::update()
{
    bn::optional<scene_type> result;

    if (_prepare_to_leave)
    {
        result = scene_type::TEST_3D;
    }
    else if (bn::keypad::start_pressed())
    {
        _prepare_to_leave = true;
    }
    else
    {
        bn::fixed old_phi = _model->phi();
        bn::fixed old_theta = _model->theta();
        bn::fixed old_psi = _model->psi();
        // // Remember to avoid Gymball lock with the following
        // _model->set_psi(0);
        // _model->set_theta(0);
        _model->set_phi(old_phi + 300);
        // _model->set_theta(old_theta);
        // _model->set_psi(old_psi);
    }

    _models.update(_camera);

    return result;
}
