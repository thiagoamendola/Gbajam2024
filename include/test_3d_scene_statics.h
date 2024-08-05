
#include "static_model_3d_item.h"

#include "models/bush.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

constexpr auto _bush_model =
    static_model_3d_item<fr::model_3d_items::bush_full>(
        fr::point_3d(30, 750, 40), 16000);
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
    _bush_model_3.item(),    _bush_model_2.item(),    _bush_model.item(),
    _bush_model_4.item(),    _bush_model__2.item(),   _bush_model_2__2.item(),
    _bush_model_3__2.item(), _bush_model_4__2.item(), _bush_model_5.item(),
    _bush_model_6.item(),    _bush_model_7.item(),    _bush_model_5__2.item(),
    _bush_model_6__2.item(), _bush_model_7__2.item()

};
