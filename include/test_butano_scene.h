#ifndef TEST_BUTANO_SCENE_H
#define TEST_BUTANO_SCENE_H

#include "bn_regular_bg_ptr.h"
#include "bn_bg_palettes_actions.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_position_hbe_ptr.h"

#include "fr_scene.h"

#include "scene_type.h"
#include "controller.h"

class test_butano_scene : public fr::scene
{

public:
    test_butano_scene();

    [[nodiscard]] bn::optional<scene_type> update() final;

private:
    void controller_move_update();
    void controller_vfx_update();
    void arrow_update();
    void ninja_update();
    void bg_upgrade();

    Controller controller;

    bn::bg_palettes_fade_to_action bgs_fade_in_action;
    bn::vector<bn::sprite_ptr, 32> text_sprites;

    // Controller sprite
    bn::sprite_ptr controller_spr;

    // Set controller effect
    bn::array<bn::fixed, bn::display::height()> horizontal_deltas;
    bn::sprite_position_hbe_ptr horizontal_position_hbe;
    bn::fixed base_degrees_angle;

    // Arrow sprite
    bn::sprite_ptr arrow_spr;

    // Ninja animated sprite
    bn::sprite_ptr ninja_spr;
    bn::sprite_animate_action<4> ninja_action;

    // Background
    bn::regular_bg_ptr floor_bg;
};

#endif
