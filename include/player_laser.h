#ifndef PLAYER_LASER_H
#define PLAYER_LASER_H

#include "bn_colors.h"

#include "fr_model_3d_item.h"
#include "fr_model_colors.h"

class player_laser
{
  public:
    player_laser();

    // Calculates wether laser is being used, collision and so on.
    void handle_player_laser();

    // Controls laser mesh render as a static model (at the end of update)
    int render_player_laser(fr::point_3d player_ship_pos,
                            const fr::model_3d_item **static_model_items,
                            int static_count);

  private:
    fr::vertex_3d laser_vertices[6] = {
        fr::vertex_3d(1, 0, 0), fr::vertex_3d(0, 1, 0), fr::vertex_3d(0, 0, 1),
        fr::vertex_3d(1, 1, 0), fr::vertex_3d(0, 1, 1), fr::vertex_3d(1, 0, 1),
    };

    //     Maybe I need to define the Normal vector! Check Python

    //     def normal(p0, p1, p2):
    //         # cross_product = np.cross(p1 - p0, p2 - p0)
    //         cross_product = cross(sub(p1, p0), sub(p2, p0))
    //         # normal = cross_product / np.linalg.norm(cross_product)
    //         magnitude = norm(cross_product)
    //         return [cross_product[0] / magnitude, cross_product[1] /
    //    magnitude, cross_product[2] / magnitude]

    //     But let's skip it for now. I can prob mock the normal for now

    fr::face_3d laser_faces[4] = {
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 1, 2, 0, 7),
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 2, 1, 0, 7),
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 3, 4, 5, 0, 7),
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 3, 5, 4, 0, 7),
    };

    bn::color laser_colors[1] = {
        bn::color(24, 0, 0),
    };

    fr::model_3d_item laser_full;

    bool render_laser = false;
};

#endif