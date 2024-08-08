#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "fr_model_3d.h"
#include "fr_model_3d_item.h"

class collision_detection
{
  public:
    static bool is_colliding_with_static(
        fr::model_3d *model, bn::span<const fr::model_3d_item> _model_items);

    // static bool is_colliding_with_dynamic(fr::model_3d *model1,
    //                                       fr::model_3d *model2);
};

#endif