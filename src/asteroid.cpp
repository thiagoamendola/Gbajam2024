#include "asteroid.h"

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_sound_items.h"
#include "bn_string.h"

#include "fr_point_3d.h"

#include "models/asteroid1.h"

// <-- Implement definition from header

asteroid::asteroid(fr::point_3d position, fr::point_3d movement, fr::models_3d *models, controller *controller)
    : _position(position), _movement(movement), _models(models), _controller(controller),
      _sphere_collider_set(fr::model_3d_items::asteroid_colliders)
{
    _model =
        &_models->create_dynamic_model(fr::model_3d_items::asteroid1_full);
    _model->set_position(position);

}

void asteroid::update()
{
    // <-- IMPLEMENT

    // Rotate.
    _model->set_phi(_model->phi() + 600); // <-- Magic number

    _sphere_collider_set.set_origin(get_model()->position());
}

void asteroid::destroy()
{
    _models->destroy_dynamic_model(*_model);
}

int asteroid::statics_render(const fr::model_3d_item **static_model_items,
                       int static_count)
{
    int current_static_count = static_count;

    // Render debug collider models
    if (_controller->is_collider_display_enabled())
    {
        current_static_count = _sphere_collider_set.debug_collider(
            static_model_items, current_static_count);
    }

    return current_static_count;
}

