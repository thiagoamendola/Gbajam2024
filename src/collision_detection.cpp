
#include "collision_detection.h"

#include "bn_span.h"

#include "fr_model_3d.h"
#include "fr_model_3d_item.h"

bool collision_detection::is_colliding_with_static(
    fr::model_3d *model, bn::span<const fr::model_3d_item> _model_items)
{
    // // const model_3d_item* model_items = stage.model_items().data();
    // // const model_3d_grid::cell* grid_cells = stage.model_grid().cells();

    // for (const point_3d &collision_point : player_car.collision_points())
    // {
    //     bn::point
    //     collision_point_2d(collision_point.x().right_shift_integer(),
    //                                  collision_point.z().right_shift_integer());
    //     int row = _row(collision_point);
    //     int column = _column(collision_point);
    //     // const model_3d_grid::cell* grid_cells_row = grid_cells + (row *
    //     model_3d_grid::columns);
    //     // const model_3d_grid::cell& grid_cell = grid_cells_row[column];

    //     for (int index = 0, limit = grid_cell.models_count; index < limit;
    //          ++index)
    //     {
    //         int model_index = grid_cell.model_indexes[index];
    //         const model_3d_item &model_item = model_items[model_index];

    //         if (const face_3d *collision_face = model_item.collision_face())
    //         {
    //             const vertex_3d *vertices = model_item.vertices().data();
    //             const point_3d &v0 =
    //                 vertices[collision_face->first_vertex_index()].point();
    //             const point_3d &v1 =
    //                 vertices[collision_face->second_vertex_index()].point();
    //             const point_3d &v2 =
    //                 vertices[collision_face->third_vertex_index()].point();
    //             bn::point v0_point(v0.x().right_shift_integer(),
    //                                v0.z().right_shift_integer());
    //             bn::point v1_point(v1.x().right_shift_integer(),
    //                                v1.z().right_shift_integer());
    //             bn::point v2_point(v2.x().right_shift_integer(),
    //                                v2.z().right_shift_integer());
    //             int winding_number =
    //                 _winding_number(v0_point, v1_point, collision_point_2d);
    //             winding_number +=
    //                 _winding_number(v1_point, v2_point, collision_point_2d);

    //             if (collision_face->triangle())
    //             {
    //                 winding_number +=
    //                     _winding_number(v2_point, v0_point,
    //                     collision_point_2d);
    //             }
    //             else
    //             {
    //                 const point_3d &v3 =
    //                     vertices[collision_face->fourth_vertex_index()].point();
    //                 bn::point v3_point(v3.x().right_shift_integer(),
    //                                    v3.z().right_shift_integer());
    //                 winding_number +=
    //                     _winding_number(v2_point, v3_point,
    //                     collision_point_2d);
    //                 winding_number +=
    //                     _winding_number(v3_point, v0_point,
    //                     collision_point_2d);
    //             }

    //             if (winding_number)
    //             {
    //                 player_car.crash();
    //                 announcer.play_wall_crash_voice(45);
    //                 return;
    //             }
    //         }
    //     }
    // }

    return false;
}