#include "colliders.h"

#include "bn_colors.h"
#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_constants_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "fr_point_3d.h"

int sphere_collider_set::debug_collider(
    fr::point_3d origin_pos, const fr::model_3d_item **static_model_items,
    int static_count)
{
    // <-- for each
    auto collider = _sphere_collider_list[0];

    // Calc vertices
    _sphere_collider_debugger.debug_vertices[0].reset(
        origin_pos + collider.position + fr::point_3d(collider.radius, 0, 0));
    _sphere_collider_debugger.debug_vertices[1].reset(
        origin_pos + collider.position + fr::point_3d(0, 0, collider.radius));
    _sphere_collider_debugger.debug_vertices[2].reset(
        origin_pos + collider.position + fr::point_3d(-collider.radius, 0, 0));
    _sphere_collider_debugger.debug_vertices[3].reset(
        origin_pos + collider.position + fr::point_3d(0, 0, -collider.radius));

    // Calc faces
    _sphere_collider_debugger.debug_faces[0].reset(
        _sphere_collider_debugger.debug_vertices, fr::vertex_3d(0, 1, 0), 2, 1,
        0, 0, 7);
    _sphere_collider_debugger.debug_faces[1].reset(
        _sphere_collider_debugger.debug_vertices, fr::vertex_3d(0, 1, 0), 0, 3,
        2, 0, 7);

    // Add mesh as static object
    if (static_count >= fr::constants_3d::max_static_models)
    {
        BN_LOG("[debug_collider] Stage Section Renderer: reached static "
               "model max "
               "limit: " +
               bn::to_string<64>(fr::constants_3d::max_static_models));
        return static_count;
    }
    static_model_items[static_count] = &_sphere_collider_debugger.debug_model;
    static_count += 1;

    // BN_LOG("[debug_collider] Added collider. Count: " +
    //        bn::to_string<64>(static_count));

    return static_count;
}