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
            const auto colors_span = raw_scene_colors[i];
            const auto colors_raw = colors_span.data();

            int color_index = 0;

            for (auto color : colors_span)
            {
                // Find color in scene_colors and add index
                for (size_t j = 0; j < scene_palette_size; j++)
                {
                    if (scene_colors[j] == color)
                    {
                        _color_map[colors_raw][color_index] = j;
                        break;
                    }
                }

                color_index++;
            }
        }
    }

    int get_index(int index, const bn::color *model_color)
    {
        return _color_map[model_color][index];
    }

    size_t _model_palette_count;
    size_t _scene_palette_size;

    bn::unordered_map<const bn::color *, bn::array<int, MAX_COLORS>, MAX_MODELS>
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

} // namespace scene_colors_generator

#endif
