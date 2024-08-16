
#include "scene_colors_generator.h"
#include "static_model_3d_item.h"

#include "bn_color.h"
#include "bn_span.h"

#include "models/bush.h"
#include "models/player_ship_02.h"
#include "models/shot.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// Static Models

constexpr auto _bush_model =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 750, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 650, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_3 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 550, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_4 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 450, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_5 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 350, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_6 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 250, 40), 16000, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_7 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 150, 40), 16000, fr::model_3d_items::bush_colors);

constexpr auto _bush_model__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 750, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_2__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 650, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_3__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 550, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_4__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 450, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_5__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 350, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_6__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 250, 40), 0, fr::model_3d_items::bush_colors);
constexpr auto _bush_model_7__2 =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(-30, 150, 40), 0, fr::model_3d_items::bush_colors);

constexpr fr::model_3d_item static_model_items[] = {
    _bush_model.item(),      _bush_model_3.item(),    _bush_model_2.item(),
    _bush_model_4.item(),    _bush_model__2.item(),   _bush_model_2__2.item(),
    _bush_model_3__2.item(), _bush_model_4__2.item(), _bush_model_5.item(),
    _bush_model_6.item(),    _bush_model_7.item(),    _bush_model_5__2.item(),
    _bush_model_6__2.item(), _bush_model_7__2.item()

};

// - Colors

// Add materials here
constexpr const auto raw_scene_colors = {
    bn::span<const bn::color>(fr::model_3d_items::player_ship_02_colors),
    bn::span<const bn::color>(fr::model_3d_items::bush_colors),
    bn::span<const bn::color>(fr::model_3d_items::shot_colors),

};

constexpr size_t total_color_count =
    scene_colors_generator::calculate_total_size(raw_scene_colors);

// Load this
constexpr auto scene_colors =
    scene_colors_generator::generate_scene_colors<total_color_count>(
        raw_scene_colors);

constexpr auto scene_color_mapping =
    scene_colors_generator::generate_scene_color_mapping<
        raw_scene_colors.size(), total_color_count>(raw_scene_colors,
                                                    scene_colors);
