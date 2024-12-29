#ifndef COLLIDERS_H
#define COLLIDERS_H

#include "bn_array.h"
#include "bn_colors.h"
#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_span.h"
#include "bn_string.h"
#include "bn_vector.h"

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

template <size_t ColliderNum> class sphere_collider_set
{
  public:
    constexpr sphere_collider_set(
        const bn::span<const sphere_collider> &sphere_colliders)
        : _sphere_collider_list(sphere_colliders), 
        _sphere_collider_debuggers()
    {
    }

    int debug_collider(fr::point_3d origin_pos,
                       const fr::model_3d_item **static_model_items,
                       int static_count)
    {
        for (size_t i = 0; i < ColliderNum; i++)
        {
            auto collider = _sphere_collider_list[i];

            // Calc vertices
            _sphere_collider_debuggers[i].debug_vertices[0].reset(
                origin_pos + collider.position + fr::point_3d(collider.radius, 0, 0));
            _sphere_collider_debuggers[i].debug_vertices[1].reset(
                origin_pos + collider.position + fr::point_3d(0, 0, collider.radius));
            _sphere_collider_debuggers[i].debug_vertices[2].reset(
                origin_pos + collider.position + fr::point_3d(-collider.radius, 0, 0));
            _sphere_collider_debuggers[i].debug_vertices[3].reset(
                origin_pos + collider.position + fr::point_3d(0, 0, -collider.radius));

            // Calc faces
            _sphere_collider_debuggers[i].debug_faces[0].reset(
                _sphere_collider_debuggers[i].debug_vertices, fr::vertex_3d(0, 1, 0), 2, 1,
                0, 0, 7);
            _sphere_collider_debuggers[i].debug_faces[1].reset(
                _sphere_collider_debuggers[i].debug_vertices, fr::vertex_3d(0, 1, 0), 0, 3,
                2, 0, 7);

            // Add mesh as static object
            if (static_count >= fr::constants_3d::max_static_models)
            {
                BN_LOG("[debug_collider] Stage Section Renderer: reached static model max limit: " +
                    bn::to_string<64>(fr::constants_3d::max_static_models));
                return static_count;
            }
            static_model_items[static_count] = &_sphere_collider_debuggers[i].debug_model;
            static_count += 1;

            // BN_LOG("[debug_collider] Added collider. Count: " +
            //        bn::to_string<64>(static_count));
        }

        return static_count;
    }

  private:
    const bn::span<const sphere_collider> _sphere_collider_list;
    bn::array<sphere_collider_debugger, ColliderNum> _sphere_collider_debuggers;
};

#endif
