
#include "bn_core.h"
#include "bn_memory.h"
#include "bn_keypad.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_ptr.h"
#include "bn_display.h"
#include "bn_math.h"
#include "common_variable_8x16_sprite_font.h"

// #include "fr_scene_type.h"
// #include "fr_common_stuff.h"
// #include "fr_jam_intro_scene.h"
// #include "fr_butano_intro_scene.h"

#include "controller.h"
// #include "test_scene.h"

#include "bn_sprite_items_controller.h"
#include "bn_sprite_items_arrow.h"
#include "bn_sprite_items_ninja.h"
#include "bn_regular_bg_items_floor.h"

#if FR_PROFILE
#include "bn_log.h"
#endif

void controller_move_update(
    Controller &controller,
    bn::sprite_ptr &controller_spr)
{
    // Get raw input vector
    bn::fixed_point dir_input = controller.get_smooth_directional();

    // Set value
    bn::fixed controller_distance = 30;

    controller_spr.set_y(dir_input.y() * controller_distance);
    controller_spr.set_x(dir_input.x() * controller_distance);
}

void controller_vfx_update(
    bn::fixed &base_degrees_angle,
    bn::array<bn::fixed, bn::display::height()> &horizontal_deltas,
    bn::sprite_position_hbe_ptr &horizontal_position_hbe)
{
    if (bn::keypad::a_held())
    {
        base_degrees_angle += 4;

        if (base_degrees_angle >= 360)
        {
            base_degrees_angle -= 360;
        }

        bn::fixed degrees_angle = base_degrees_angle;

        for (int index = 0, limit = bn::display::height() / 2; index < limit; ++index)
        {
            degrees_angle += 16;

            if (degrees_angle >= 360)
            {
                degrees_angle -= 360;
            }

            bn::fixed desp = bn::degrees_lut_sin(degrees_angle) * 6;
            horizontal_deltas[(bn::display::height() / 2) + index] = desp;
            horizontal_deltas[(bn::display::height() / 2) - index - 1] = desp;
        }

        horizontal_position_hbe.reload_deltas_ref();
    }
    else
    {
        for (int index = 0, limit = bn::display::height() / 2; index < limit; ++index)
        {
            horizontal_deltas[(bn::display::height() / 2) + index] = 0;
            horizontal_deltas[(bn::display::height() / 2) - index - 1] = 0;
        }
        horizontal_position_hbe.reload_deltas_ref();
    }
}

void arrow_update(bn::sprite_ptr &arrow_spr)
{
    if (bn::keypad::left_held())
    {
        arrow_spr.set_tiles(bn::sprite_items::arrow.tiles_item().create_tiles(2));
    }
    else if (bn::keypad::right_held())
    {
        arrow_spr.set_tiles(bn::sprite_items::arrow.tiles_item().create_tiles(3));
    }

    if (bn::keypad::up_held())
    {
        arrow_spr.set_tiles(bn::sprite_items::arrow.tiles_item().create_tiles(0));
    }
    else if (bn::keypad::down_held())
    {
        arrow_spr.set_tiles(bn::sprite_items::arrow.tiles_item().create_tiles(1));
    }
}

void ninja_update(bn::sprite_ptr &ninja_spr, bn::sprite_animate_action<4> &action)
{
    if (bn::keypad::left_pressed())
    {
        action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 8, 9, 10, 11);
    }
    else if (bn::keypad::right_pressed())
    {
        action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 12, 13, 14, 15);
    }

    if (bn::keypad::up_pressed())
    {
        action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 4, 5, 6, 7);
    }
    else if (bn::keypad::down_pressed())
    {
        action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 0, 1, 2, 3);
    }

    action.update();
}

void bg_upgrade()
{
}

int main()
{
#if FR_PROFILE
    // constexpr const char *profile_keys =
    //     "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    //     "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010A0A0A0A0A0A0A0"
    //     "A0A0A0A0A0A01010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111111111101010101010101010101010101010101010101010"
    //     "1010A0A0A0A0A0A01010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A01010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010"
    //     "10A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010A0A0A0A0A010101010101010101818181818181818A8A8A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010101010101010101010"
    //     "101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010101010101010101011111111111111111111111111111111111111111111111110101010101010101010101010101010101111111111111111111111111111111111111111111111111111111111111111111111"
    //     "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110101010101010101010101010111111111111111111111111111111111111111111111111111111101010101010101010101010101010101111111111111110"
    //     "1010101010101010101010101010101010101010101010101010111111111111111110101010101010101010101010101010101010101010101010101011111111111111111111111010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010A0A0"
    //     "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0"
    //     "A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010101010101010101010101010181818181818181818181810101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111111111111111111111111111"
    //     "1110101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010101010A0A0A0A0A0A0A0A0101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010A0A0A0A0A0A0"
    //     "A0A0A0A0A0A010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111101010101010101010101010101010101010101010101011111111101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010101010101010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    // bn::core::init(profile_keys);
    bn::core::init();

    BN_LOG("iwram: ", bn::memory::used_static_iwram());
    BN_LOG("ewram: ", bn::memory::used_static_ewram());

#else
    bn::core::init();

#endif

    // bn::unique_ptr<fr::common_stuff> common_stuff(new fr::common_stuff());
    // bn::optional<fr::scene_type> next_scene = fr::scene_type::BUTANO_INTRO;
    // bn::unique_ptr<fr::scene> scene;

    bn::bg_palettes_fade_to_action bgs_fade_in_action(1, 0);

    Controller controller;

    while (true)
    {
        // MY DEMO 1

        {
            bgs_fade_in_action.update();

            // Set background color
            bn::bg_palettes::set_transparent_color(bn::color(22, 28, 31));

            // Set text
            bn::vector<bn::sprite_ptr, 32> text_sprites;
            bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
            text_generator.generate(-6 * 16, -68, "Hello I'm some text yey", text_sprites);

            // Set sprite
            bn::sprite_ptr controller_spr = bn::sprite_items::controller.create_sprite(0, 0);
            controller_spr.set_scale(2);

            // Set controller effect
            bn::array<bn::fixed, bn::display::height()> horizontal_deltas;
            bn::sprite_position_hbe_ptr horizontal_position_hbe =
                bn::sprite_position_hbe_ptr::create_horizontal(controller_spr, horizontal_deltas);
            bn::fixed base_degrees_angle;

            // Set changeable sprite
            bn::sprite_ptr arrow_spr = bn::sprite_items::arrow.create_sprite(100, 60);
            // arrow_spr.set_scale(2);

            // Set animate sprite
            bn::sprite_ptr ninja_spr = bn::sprite_items::ninja.create_sprite(-100, 60);
            bn::sprite_animate_action<4> ninja_action = bn::create_sprite_animate_action_forever(
                ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 0, 1, 2, 3);

            // Set background
            bn::regular_bg_ptr floor_bg = bn::regular_bg_items::floor.create_bg(0, 0);

            while (!bn::keypad::start_pressed())
            {
                controller_vfx_update(
                    base_degrees_angle,
                    horizontal_deltas,
                    horizontal_position_hbe);

                // Move controller
                controller_move_update(controller, controller_spr);

                arrow_update(arrow_spr);
                ninja_update(ninja_spr, ninja_action);

                // Update frame
                bn::core::update();
            }

            bn::core::update();
        }

        // TEST 3D SCENE

        // scene.reset(new test_scene());
        // next_scene.reset();
        // common_stuff->update();
        // bn::core::update();

        // while (!next_scene)
        // {
        //     next_scene = scene->update();
        //     common_stuff->update();
        //     bn::core::update();
        // }

        // scene.reset();
        // common_stuff->update();
        // bn::core::update();

        // // BUTANO INTRO
        // scene.reset(new fr::butano_intro_scene(*common_stuff));
        // next_scene.reset();
        // common_stuff->update();
        // bn::core::update();

        // while (!next_scene)
        // {
        //     next_scene = scene->update();
        //     common_stuff->update();
        //     bn::core::update();
        // }

        // scene.reset();
        // common_stuff->update();
        // bn::core::update();

        // // GBA JAM INTRO
        // scene.reset(new fr::jam_intro_scene());
        // next_scene.reset();
        // common_stuff->update();
        // bn::core::update();

        // while (!next_scene)
        // {
        //     next_scene = scene->update();
        //     common_stuff->update();
        //     bn::core::update();
        // }

        // scene.reset();
        // common_stuff->update();
        // bn::core::update();
    }
}
