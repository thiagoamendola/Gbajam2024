#ifndef SCENE_COLOR_GENERATOR_H
#define SCENE_COLOR_GENERATOR_H

#include <initializer_list>

#include "bn_array.h"
#include "bn_color.h"
#include "bn_span.h"
#include "bn_unordered_map.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

namespace scene_colors_generator
{

// Struct for model color mapping since std::maps are not literal and can't be
// constexpr
template <size_t scene_color_size> struct color_mapping_entry
{
    bn::array<const bn::span<const bn::color> *, scene_color_size> colors_span;
    bn::array<bn::array<int, 16>, scene_color_size> mapping_array;
};

// Get full size of final scene color array (does not count for repeated)
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

//
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

//
template <size_t full_size, size_t scene_color_size>
constexpr color_mapping_entry<scene_color_size> generate_scene_color_mapping(
    const std::initializer_list<bn::span<const bn::color>> raw_scene_colors,
    bn::array<bn::color, full_size> scene_colors)
{
    color_mapping_entry<scene_color_size> scene_color_mapping = {};

    for (size_t i = 0; i < scene_color_size; ++i)
    {
        const auto *colors_span = &*(raw_scene_colors.begin() + i);

        bn::array<int, 16> mapping_array = {};

        int aux = 0;

        for (auto color : *colors_span)
        {
            // Find color in scene_colors and add index
            for (int j = 0; j < scene_colors.size(); j++)
            {
                if (scene_colors[j] == color)
                {
                    mapping_array[aux] = j;
                    aux++;
                    break;
                }
            }
        }

        scene_color_mapping.colors_span[i] = colors_span;
        scene_color_mapping.mapping_array[i] = mapping_array;
    }

    return scene_color_mapping;
}

} // namespace scene_colors_generator

#endif
