#ifndef TEST_3D_SCENE_H
#define TEST_3D_SCENE_H

#include "scene_type.h"

#include "fr_scene.h"
#include "fr_camera_3d.h"
#include "fr_models_3d.h"
#include "fr_model_3d_item.h"

class test_3d_scene : public fr::scene
{

public:
    test_3d_scene();

    [[nodiscard]] bn::optional<scene_type> update() final;

private:
    fr::camera_3d _camera;
    fr::models_3d _models;
    fr::model_3d *_model;
    fr::model_3d *_model2;
    // fr::model_3d *_trees[10];
    bn::span<const fr::model_3d_item> _model_items;

    const fr::model_3d_item *_static_model_items[fr::constants_3d::max_static_models];

    bool _prepare_to_leave;
};

#endif
