
/*
 * Generated by Nikku4211's Wavefront to Varooom Converter
 * Nikku4211 - github.com/nikku4211/
 *
 */

#ifndef FR_MODEL_3D_ITEMS_shot_H
#define FR_MODEL_3D_ITEMS_shot_H

#include "fr_model_3d_item.h"

namespace fr::model_3d_items
{
    constexpr inline vertex_3d shot_vertices[] = {
        vertex_3d(12.95334, 0.22710000000000002, -0.024260000000000004),
        vertex_3d(-0.04558, 9.0689, -0.06837),
        vertex_3d(0.024260000000000004, 0.22710000000000002, 10.06563),
        vertex_3d(0.02427, -9.84092, -0.02427),
        vertex_3d(0.107, 0.22710000000000002, -9.86874),
        vertex_3d(-43.087939999999996, 0.22710000000000002, 0.024260000000000004),
    };
    constexpr inline bn::color shot_colors[] = {
        bn::color(22, 0, 7),
    };
    constexpr inline int shot_color_0 = 0;

    constexpr inline face_3d shot_faces_full[] = {
        face_3d(shot_vertices, vertex_3d(0.45538423419394086, 0.6724018299882635, 0.5835246166838486), 0, 1, 2, 0, 1),
        face_3d(shot_vertices, vertex_3d(0.4793568477558794, -0.6155760501421542, -0.6255262896161364), 3, 4, 0, 0, 3),
        face_3d(shot_vertices, vertex_3d(0.4827448891845433, -0.6199281139938096, 0.6185842751366067), 3, 0, 2, 0, 2),
        face_3d(shot_vertices, vertex_3d(-0.1623330005451338, -0.6984847427162454, 0.6969699140756607), 2, 5, 3, 0, 4),
        face_3d(shot_vertices, vertex_3d(-0.16175313735476518, -0.6892379020792947, -0.7062485659406489), 3, 5, 4, 0, 6),
        face_3d(shot_vertices, vertex_3d(0.45430482152282614, 0.6649462858496745, -0.5928351930139065), 4, 1, 0, 0, 4),
        face_3d(shot_vertices, vertex_3d(-0.1514948366147769, 0.7442992658082963, 0.6504367128293832), 2, 1, 5, 0, 5),
        face_3d(shot_vertices, vertex_3d(-0.15193690514070196, 0.732687152259055, -0.6633888104051664), 5, 1, 4, 0, 7),
    };
    constexpr inline model_3d_item shot_full(shot_vertices, shot_faces_full);
};
#endif