#ifndef COLLIDERS_H
#define COLLIDERS_H

#include "bn_colors.h"
#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_constants_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "fr_point_3d.h"

namespace fr::model_3d_items
{

constexpr inline bn::color debug_collider_colors[] = {
    bn::color(0, 0, 24),
};

}

// = Collider Debugging Classes

struct sphere_collider_debugger
{
    fr::vertex_3d debug_vertices[4] = {
        fr::vertex_3d(1, 0, 0),
        fr::vertex_3d(0, 1, 0),
        fr::vertex_3d(0, 0, 1),
        fr::vertex_3d(1, 1, 0),
    };

    fr::face_3d debug_faces[2] = {
        fr::face_3d(debug_vertices, fr::vertex_3d(0, 1, 0), 0, 1, 2, 0, 7),
        fr::face_3d(debug_vertices, fr::vertex_3d(0, 1, 0), 2, 3, 0, 0, 7),
    };

    fr::model_3d_item debug_model;

    constexpr sphere_collider_debugger()
        : debug_model(debug_vertices, debug_faces,
                      fr::model_3d_items::debug_collider_colors)
    {
    }
};

// = Colliders

struct sphere_collider
{
    fr::point_3d position;
    bn::fixed radius;

    constexpr sphere_collider(fr::point_3d _position, bn::fixed _radius)
        : position(_position), radius(_radius)
    {
    }
};

class sphere_collider_set
{
  public:
    constexpr sphere_collider_set(
        const bn::span<const sphere_collider> &sphere_colliders)
        : _sphere_collider_list(sphere_colliders), _sphere_collider_debugger()
    {
    }

    int debug_collider(fr::point_3d origin_pos,
                       const fr::model_3d_item **static_model_items,
                       int static_count);

  private:
    const bn::span<const sphere_collider> _sphere_collider_list;

    // <-- I need to create a list of sphere_collider_debuggers equal to
    // _sphere_collider_list. Not sure if I can do it at runtime

    // <-- Find a way to make it work for more!

    sphere_collider_debugger _sphere_collider_debugger;
};

#endif
