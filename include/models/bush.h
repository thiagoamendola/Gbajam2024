
/*
 * Generated by Nikku4211's Wavefront to Varooom Converter
 * Nikku4211 - github.com/nikku4211/
 *
 */

#ifndef FR_MODEL_3D_ITEMS_bush_H
#define FR_MODEL_3D_ITEMS_bush_H

#include "fr_model_3d_item.h"

namespace fr::model_3d_items
{
constexpr inline vertex_3d bush_vertices[] = {
    vertex_3d(14.1421, -0.4276, -8.2708), vertex_3d(-14.1421, -0.4276, -8.2708),
    vertex_3d(0.0, 11.2690, -0.3217),     vertex_3d(0.0, 0.0274, 16.2198),
    vertex_3d(-14.1421, 5.6208, -8.2708), vertex_3d(0.0, 6.0758, 16.2198),
};
constexpr inline bn::color bush_colors[] = {
    bn::color(0, 24, 0),
};
constexpr inline int bush_color_0 = 0;

constexpr inline face_3d bush_faces_full[] = {
    face_3d(bush_vertices, vertex_3d(0.0000, 0.5621, -0.8271), 1, 2, 0, 0, 7),
    face_3d(bush_vertices, vertex_3d(0.7071, 0.5848, 0.3975), 0, 2, 3, 0, 6),
    face_3d(bush_vertices, vertex_3d(-0.7071, 0.5848, 0.3975), 3, 2, 1, 0, 5),
};
constexpr inline model_3d_item bush_full(bush_vertices, bush_faces_full,
                                         bush_colors);
}; // namespace fr::model_3d_items
#endif