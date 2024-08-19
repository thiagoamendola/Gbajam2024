#ifndef SCENE_COLOR_GENERATOR_H
#define SCENE_COLOR_GENERATOR_H

#include <map>

#include "bn_array.h"
#include "bn_color.h"
#include "bn_span.h"
#include "bn_unordered_map.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

namespace scene_colors_generator
{

const int MAX_COLORS = 16;
const int MAX_MODELS = 16;

//
struct color_mapping_handler
{
    color_mapping_handler(size_t model_palette_count, size_t scene_palette_size,
                          const bn::span<const bn::color> *raw_scene_colors,
                          const bn::color *scene_colors

                          )
        : _model_palette_count(model_palette_count),
          _scene_palette_size(scene_palette_size)
    {
        for (size_t i = 0; i < model_palette_count; ++i)
        {
            const auto *colors_span = &raw_scene_colors[i];

            int color_index = 0;

            for (auto color : *colors_span)
            {
                // Find color in scene_colors and add index
                for (size_t j = 0; j < scene_palette_size; j++)
                {
                    if (scene_colors[j] == color)
                    {
                        _color_map[colors_span][color_index] = j;
                        break;
                    }
                }

                color_index++;
            }
        }
    }

    int get_index(int index, const bn::span<const bn::color> *model_color)
    {
        return _color_map[model_color][index];
    }

    size_t _model_palette_count;
    size_t _scene_palette_size;

    bn::unordered_map<const bn::span<const bn::color> *,
                      bn::array<int, MAX_COLORS>, MAX_MODELS>
        _color_map;
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

// //
// template <size_t full_size, size_t scene_color_size>
// constexpr color_mapping_entry<scene_color_size> generate_scene_color_mapping(
//     const std::initializer_list<bn::span<const bn::color>> raw_scene_colors,
//     bn::array<bn::color, full_size> scene_colors)
// {
//     color_mapping_entry<scene_color_size> scene_color_mapping = {};

//     for (size_t i = 0; i < scene_color_size; ++i)
//     {
//         const auto *colors_span = &*(raw_scene_colors.begin() + i);

//         bn::array<int, 16> mapping_array = {};

//         int aux = 0;

//         for (auto color : *colors_span)
//         {
//             // Find color in scene_colors and add index
//             for (int j = 0; j < scene_colors.size(); j++)
//             {
//                 if (scene_colors[j] == color)
//                 {
//                     mapping_array[aux] = j;
//                     aux++;
//                     break;
//                 }
//             }
//         }

//         scene_color_mapping.colors_span_key[i] = colors_span;
//         scene_color_mapping.mapping_index_array[i] = mapping_array;
//     }

//     return scene_color_mapping;
// }

// //
// template <size_t scene_color_size>
// int get_index(int index, const bn::span<const bn::color> *model_color,
//               color_mapping_entry<scene_color_size> color_mapping_entry)
// {
//     int final_index = -1;

//     // Find index of model_color in colors_span_key
//     int model_index = -1;
//     for (int i = 0; i < scene_color_size; ++i)
//     {
//         if (color_mapping_entry.colors_span_key[i] == model_color)
//         {
//             model_index = i;
//             break;
//         }
//     }

//     // If model_index was found, use it to access the right array in
//     // mapping_array
//     if (model_index != -1 && index >= 0 && index < 16)
//     {
//         final_index = color_mapping_entry.mapping_array[model_index][index];
//     }

//     return final_index;
// }

} // namespace scene_colors_generator

#endif
