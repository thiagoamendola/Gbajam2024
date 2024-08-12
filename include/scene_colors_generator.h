#ifndef SCENE_COLOR_GENERATOR_H
#define SCENE_COLOR_GENERATOR_H

#include <initializer_list>

#include "bn_array.h"
#include "bn_color.h"
#include "bn_span.h"
// #include "bn_unordered_set.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

namespace scene_colors_generator
{

template <size_t full_size>
constexpr bn::array<bn::color, full_size> generate_scene_colors(
    const std::initializer_list<bn::span<const bn::color>> color_list)
{
    bn::array<bn::color, full_size> color_list_vec;
    int i = 0;

    for (auto colors_span : color_list)
    {
        for (auto color : colors_span)
        {
            color_list_vec[i] = color;
            i++;
        }
    }

    return color_list_vec;
}

constexpr size_t calculate_total_size(
    const std::initializer_list<bn::span<const bn::color>> &color_list)
{
    size_t total_size = 0;
    for (const auto &colors_span : color_list)
    {
        total_size += colors_span.size();
    }
    return total_size;
}

} // namespace scene_colors_generator

#endif
