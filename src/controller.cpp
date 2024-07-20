#include "controller.h"

#include "bn_keypad.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"

#include "bn_log.h"
#include "bn_string.h"

#include "utils.h"

bn::fixed_point Controller::get_norm_directional()
{
    bn::fixed_point raw_dir_input(0.0, 0.0);

    if (bn::keypad::up_held())
    {
        raw_dir_input.set_y(-1.0);
    }
    else if (bn::keypad::down_held())
    {
        raw_dir_input.set_y(1.0);
    }

    if (bn::keypad::right_held())
    {
        raw_dir_input.set_x(1.0);
    }
    else if (bn::keypad::left_held())
    {
        raw_dir_input.set_x(-1.0);
    }

    // Normalize manually

    raw_dir_input = unit_vector(raw_dir_input);

    return raw_dir_input;
}

bn::fixed_point Controller::get_smooth_directional()
{
    bn::fixed_point current_raw_dir_input = get_norm_directional();

    bn::fixed interp_step = 0.2;

    // Check if it's different from previous one. If so, reset interpolation counter
    if (current_raw_dir_input != previous_raw_dir_input)
    {
        interp = 0;
    }

    // Move interpolation counter
    interp += interp_step;
    interp = interp > 1 ? 1 : interp;

    // Grab diff
    bn::fixed_point diff_vec = current_raw_dir_input - smooth_dir_input;

    if (bn::keypad::a_held())
    {
        BN_LOG("current: " + bn::to_string<32>(current_raw_dir_input.x()));
        BN_LOG("smooth: " + bn::to_string<32>(smooth_dir_input.x()));
        BN_LOG("diff: " + bn::to_string<32>(diff_vec.x()));
    }

    // Calculate fractional diff
    diff_vec *= interp;

    // Update smooth dir
    smooth_dir_input += diff_vec;

    if (bn::keypad::a_held())
    {
        BN_LOG("diff lerp: " + bn::to_string<32>(diff_vec.x()));
        BN_LOG("FINAL smooth: " + bn::to_string<32>(smooth_dir_input.x()));
        BN_LOG("=====================================");
    }

    /*
    There's likely an error on how we progress and subtract the diff but let's check first
    */

    previous_raw_dir_input = current_raw_dir_input;

    return smooth_dir_input;
}
