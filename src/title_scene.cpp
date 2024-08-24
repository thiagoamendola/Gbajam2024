
#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"
// #include "bn_music_items.h"
#include "bn_sound_items.h"
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

    // Set music
    // bn::music_items::amayadori.play(1);
    // bn::music_items::title.play(1);
}

bn::optional<scene_type> title_scene::update()
{
    bn::optional<scene_type> result;

    if (_prepare_to_leave)
    {
        _bgs_fade_out_action->update();
        _sprites_fade_out_action->update();
        result = scene_type::TEST_3D;
    }
    else if (_bgs_fade_out_action)
    {
        if (!_bgs_fade_out_action->done())
        {
            _bgs_fade_out_action->update();
            _sprites_fade_out_action->update();
        }
        else
        {
            _prepare_to_leave = true;
            _bgs_fade_out_action.emplace(1, 0);
            _sprites_fade_out_action.emplace(1, 0);
        }
    }
    else if (bn::keypad::start_pressed())
    {
        // Start scene transition
        bn::sound_items::menu_confirm.play();
        _bgs_fade_out_action.emplace(60, 1);
        _sprites_fade_out_action.emplace(60, 1);
    }

    _model->set_phi(_model->phi() + 300);

    _models.update(_camera);

    return result;
}
