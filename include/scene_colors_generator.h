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

//     // Convert const bn::color* to bn::color* for processing
//     bn::color *non_const_colors[color_list.size()];
//     for (std::size_t i = 0; i < color_list.size(); ++i)
//     {
//         non_const_colors[i] = const_cast<bn::color *>(color_list[i]);
//     }
//     return bn::span<bn::color>(non_const_colors, color_list.size());

// template <typename... ColorArrays>
//     constexpr auto generate_scene_colors(const ColorArrays&... arrays)
//     {
//         // Calculate the total size of all input arrays
//         constexpr int total_size = (arrays.size() + ...);

//         // Initialize the vector to store the fused colors
//         bn::vector<bn::color, total_size> fused_colors;

//         // Lambda to insert elements of each array into the vector
//         auto insert_colors = [&fused_colors](const bn::span<const bn::color>&
//         colors)
//         {
//             for(const bn::color& color : colors)
//             {
//                 fused_colors.push_back(color);
//             }
//         };

//         // Expand the parameter pack and call the lambda for each array
//         (insert_colors(arrays), ...);

//         return fused_colors;
//     }

} // namespace scene_colors_generator

#endif
