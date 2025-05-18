#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "fr_camera_3d.h"

#include "controller.h"

class ui_manager
{
public:
    ui_manager(controller *controller, fr::camera_3d *camera);

    void destroy();

    void update(); 
    void statics_update(int static_count);

private:
    controller *_controller;
    fr::camera_3d *_camera;

    // UI
    bn::sprite_text_generator _text_generator; // <-- move to common stuff
    bn::vector<bn::sprite_ptr, 32> _text_sprites;
};

#endif
