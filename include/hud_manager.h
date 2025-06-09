#ifndef HUD_MANAGER_H
#define HUD_MANAGER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "fr_camera_3d.h"

#include "controller.h"
#include "player_ship.h"

class hud_manager
{
public:
    hud_manager(controller *controller, fr::camera_3d *camera, player_ship *player_ship);

    void destroy();

    void update(); 
    void statics_update(int static_count);

private:
    controller *_controller; // <-- move to common stuff
    fr::camera_3d *_camera;
    player_ship *_player_ship;

    // UI
    bn::sprite_text_generator _text_generator; // <-- move to common stuff
    bn::vector<bn::sprite_ptr, 32> _text_sprites;
};

#endif
