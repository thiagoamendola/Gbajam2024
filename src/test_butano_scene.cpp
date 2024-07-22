// #include "bn_core.h"
#include "bn_memory.h"
#include "bn_keypad.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_text_generator.h"
// #include "bn_sprite_ptr.h"
// #include "bn_bg_palettes.h"
#include "bn_bg_palettes_actions.h"
#include "bn_colors.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_ptr.h"
#include "bn_display.h"
#include "bn_math.h"
#include "common_variable_8x16_sprite_font.h"

#include "test_butano_scene.h"

#include "bn_sprite_items_controller.h"
#include "bn_sprite_items_arrow.h"
#include "bn_sprite_items_ninja.h"
#include "bn_regular_bg_items_floor.h"

test_butano_scene::test_butano_scene() : bgs_fade_in_action(bn::bg_palettes_fade_to_action(1, 0)),
                                         controller_spr(bn::sprite_items::controller.create_sprite(0, 0)),
                                         horizontal_position_hbe(bn::sprite_position_hbe_ptr::create_horizontal(controller_spr, horizontal_deltas)),
                                         arrow_spr(bn::sprite_items::arrow.create_sprite(100, 60)),
                                         ninja_spr(bn::sprite_items::ninja.create_sprite(-100, 60)),
                                         ninja_action(bn::create_sprite_animate_action_forever(
                                             ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 0, 1, 2, 3)),
                                         floor_bg(bn::regular_bg_items::floor.create_bg(0, 0))
{
    bgs_fade_in_action.update();

    // Set background color
    bn::bg_palettes::set_transparent_color(bn::color(22, 28, 31));

    // Set text
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.generate(-6 * 16, -68, "Hello I'm some text yey", text_sprites);

    controller_spr.set_scale(2);
}

bn::optional<scene_type> test_butano_scene::update()
{
    bn::optional<scene_type> result;

    if (!bn::keypad::start_pressed())
    {
        controller_vfx_update();

        // Move controller
        controller_move_update();

        arrow_update();
        ninja_update();
        bg_upgrade();
    }
    else
    {
        // <-- Point to next scene
    }

    // Update frame
    // bn::core::update(); // <-- REMOVE

    return result;
}

void test_butano_scene::controller_move_update()
{
    // Get raw input vector
    bn::fixed_point dir_input = controller.get_smooth_directional();

    // Set value
    bn::fixed controller_distance = 30;

    controller_spr.set_y(dir_input.y() * controller_distance);
    controller_spr.set_x(dir_input.x() * controller_distance);
}

void test_butano_scene::controller_vfx_update()
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

void test_butano_scene::arrow_update()
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

void test_butano_scene::ninja_update()
{
    if (bn::keypad::left_pressed())
    {
        ninja_action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 8, 9, 10, 11);
    }
    else if (bn::keypad::right_pressed())
    {
        ninja_action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 12, 13, 14, 15);
    }

    if (bn::keypad::up_pressed())
    {
        ninja_action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 4, 5, 6, 7);
    }
    else if (bn::keypad::down_pressed())
    {
        ninja_action = bn::create_sprite_animate_action_forever(
            ninja_spr, 16, bn::sprite_items::ninja.tiles_item(), 0, 1, 2, 3);
    }

    ninja_action.update();
}

void test_butano_scene::bg_upgrade()
{
}
