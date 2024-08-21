
#include "scene_colors_generator.h"
#include "static_model_3d_item.h"

#include "bn_color.h"
#include "bn_span.h"

// #include "bn_sprite_items_ninja.h"
#include "models/bush.h"
#include "models/player_ship_02.h"
#include "models/shot.h"

using namespace scene_colors_generator;

// Static Models

constexpr auto _bush_model =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 750, 40), 16000, fr::model_3d_items::shot_colors);
constexpr auto _bush_model_2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 650, 40), 16000);
constexpr auto _bush_model_3 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 550, 40), 16000);
constexpr auto _bush_model_4 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 450, 40), 16000);
constexpr auto _bush_model_5 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 350, 40), 16000);
constexpr auto _bush_model_6 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 250, 40), 16000);
constexpr auto _bush_model_7 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 150, 40), 16000);

constexpr auto _bush_model__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 750, 40), 0);
constexpr auto _bush_model_2__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 650, 40), 0);
constexpr auto _bush_model_3__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 550, 40), 0);
constexpr auto _bush_model_4__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 450, 40), 0);
constexpr auto _bush_model_5__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 350, 40), 0);
constexpr auto _bush_model_6__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 250, 40), 0);
constexpr auto _bush_model_7__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 150, 40), 0);

constexpr fr::model_3d_item static_model_items[] = {
    _bush_model.item(),      _bush_model_3.item(),    _bush_model_2.item(),
    _bush_model_4.item(),    _bush_model__2.item(),   _bush_model_2__2.item(),
    _bush_model_3__2.item(), _bush_model_4__2.item(), _bush_model_5.item(),
    _bush_model_6.item(),    _bush_model_7.item(),    _bush_model_5__2.item(),
    _bush_model_6__2.item(), _bush_model_7__2.item()

};

// - Colors

// Add model materials here
constexpr const auto raw_scene_colors = {
    bn::span<const bn::color>(fr::model_3d_items::shot_colors),
    bn::span<const bn::color>(fr::model_3d_items::player_ship_02_colors),
    bn::span<const bn::color>(fr::model_3d_items::bush_colors),

};

constexpr size_t model_palette_count = raw_scene_colors.size();
constexpr size_t scene_palette_size = calculate_total_size(raw_scene_colors);
constexpr const bn::span<const bn::color> *raw_scene_color_ptr =
    raw_scene_colors.begin();

// Load these:
constexpr bn::array<bn::color, scene_palette_size> scene_colors =
    generate_scene_colors<scene_palette_size>(raw_scene_colors);

color_mapping_handler *color_mapping()
{
    return new color_mapping_handler(model_palette_count, scene_palette_size,
                                     raw_scene_color_ptr, scene_colors.data());
};
