#include "colliders.h"

#include "bn_colors.h"
#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_constants_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "fr_point_3d.h"

// template <size_t ColliderNum>
// sphere_collider_set<ColliderNum>::sphere_collider_set(
//     // const bn::vector<sphere_collider, ColliderNum> &sphere_colliders)
//     const sphere_collider *const &sphere_colliders)

//     : _sphere_collider_list(sphere_colliders, ColliderNum)
// {
// }

// template <size_t ColliderNum>
// int sphere_collider_set<ColliderNum>::debug_collider(
//     fr::point_3d origin_pos, const fr::model_3d_item **static_model_items,
//     int static_count)
// {
//     for (int i = 0; i < ColliderNum; ++i)
//     {
//         // auto collider_span = _sphere_collider_list[i];
//         // auto collider = collider_span.data();
//         auto collider = _sphere_collider_list[i];
//         auto collider_debugger = _sphere_collider_debuggers[i];

//         // Calc vertices
//         collider_debugger.debug_vertices[0].reset(
//             origin_pos + collider.position +
//             fr::point_3d(collider.radius, 0, 0));
//         collider_debugger.debug_vertices[1].reset(
//             origin_pos + collider.position +
//             fr::point_3d(0, 0, collider.radius));
//         collider_debugger.debug_vertices[2].reset(
//             origin_pos + collider.position +
//             fr::point_3d(-collider.radius, 0, 0));
//         collider_debugger.debug_vertices[3].reset(
//             origin_pos + collider.position +
//             fr::point_3d(0, 0, -collider.radius));

//         // Calc faces
//         collider_debugger.debug_faces[0].reset(collider_debugger.debug_vertices,
//                                                fr::vertex_3d(0, 1, 0), 2, 1,
//                                                0, 0, 7);
//         collider_debugger.debug_faces[1].reset(collider_debugger.debug_vertices,
//                                                fr::vertex_3d(0, 1, 0), 0, 3,
//                                                2, 0, 7);

//         // Add mesh as static object
//         if (static_count >= fr::constants_3d::max_static_models)
//         {
//             BN_LOG("[debug_collider] Stage Section Renderer: reached static "
//                    "model max "
//                    "limit: " +
//                    bn::to_string<64>(fr::constants_3d::max_static_models));
//             return static_count;
//         }
//         static_model_items[static_count] = &collider_debugger.debug_model;
//         static_count += 1;

//         // BN_LOG("[debug_collider] Added collider. Count: " +
//         //        bn::to_string<64>(static_count));
//     }

//     return static_count;
// }