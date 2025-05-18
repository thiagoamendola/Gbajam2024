#include "ui_manager.h"

#include "bn_sprite_text_generator.h"
#include "bn_string.h"

#include "fr_camera_3d.h"

#include "controller.h"

#include "common_variable_8x16_sprite_font.h"

ui_manager::ui_manager(controller *controller, fr::camera_3d *camera)
    : _controller(controller), _camera(camera), _text_generator(common::variable_8x16_sprite_font)
{
}

void ui_manager::destroy()
{
}

void ui_manager::update()
{
    _text_sprites.clear();

    // text generators should be created only once
    if (_controller->is_debug_text_enabled())
    {
        _text_generator.generate(-7 * 16, -72, "Location (Y): " + bn::to_string<64>(int(_camera->position().y())),
                                 _text_sprites);
    }
}

// int ui_manager::statics_render(const fr::model_3d_item **static_model_items,
//     int static_count)
// {

// }
