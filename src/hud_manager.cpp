#include "hud_manager.h"

#include "bn_sprite_text_generator.h"
#include "bn_string.h"

#include "fr_camera_3d.h"

#include "controller.h"

#include "common_variable_8x16_sprite_font.h"

hud_manager::hud_manager(controller *controller, fr::camera_3d *camera)
    : _controller(controller), _camera(camera), _text_generator(common::variable_8x16_sprite_font)
{
}

void hud_manager::destroy()
{
}

void hud_manager::update()
{
    // Clear texts.
    _text_sprites.clear();

    // text generators should be created only once // <-- what to do with this?
    
    // Display location Y debug text.
    if (_controller->is_debug_text_enabled())
    {
        _text_generator.generate(-7 * 16, -72, "Location (Y): " + bn::to_string<64>(int(_camera->position().y())),
                                 _text_sprites);
    }
}


void hud_manager::statics_update(int static_count)
{
    // Display static count debug text.
    if (_controller->is_debug_text_enabled())
    {
        _text_generator.generate(-7 * 16, -60, "Static Objs: " + bn::to_string<64>(static_count),
            _text_sprites);
    }
}
