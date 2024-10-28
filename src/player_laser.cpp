#include "player_laser.h"

#include "bn_colors.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_string.h"
// #include "bn_fixed.h"

#include "fr_model_3d_item.h"
// #include "fr_camera_3d.h"
// #include "fr_models_3d.h"

// #include "stage_section.h"
#include "player_ship.h"

int player_laser::handle_player_laser(
    player_ship *_player_ship, const fr::model_3d_item **static_model_items,
    int static_count)
{
    if (bn::keypad::a_held())
    {
        return player_laser::render_player_laser(
            _player_ship, static_model_items, static_count);
    }
    return static_count;
}

int player_laser::render_player_laser(
    player_ship *_player_ship, const fr::model_3d_item **static_model_items,
    int static_count)
{
    // HAD TO ROLL BACK CUZ STATIC METHODS WON'T WORK HERE
    // Organize vertices
    /* Test Triangle points:
        1. player ship position
        2. player ship position + {500, 0, 0}
        3. {0,player ship y,0}
    */
    fr::vertex_3d laser_vertices[] = {
        fr::vertex_3d(_player_ship->get_model()->position()),
        fr::vertex_3d(_player_ship->get_model()->position() +
                      fr::point_3d(700, 0, 0)),
        fr::vertex_3d(0, _player_ship->get_model()->position().y(), 0),
    };

    BN_LOG("PLAYER LASER: ship location: " +
           bn::to_string<64>(laser_vertices[0].point().y()));

    // Organize faces
    /* How can I define a face

        I'd like to have 2 faces: one for each side of the triangle plane

        constexpr face_3d(const bn::span<const vertex_3d> &vertices,
                      const vertex_3d &normal, int first_vertex_index,
                      int second_vertex_index, int third_vertex_index,
                      int color_index, int shading)

        > But I need to make the Normal vector! Check Python

        def normal(p0, p1, p2):
            # cross_product = np.cross(p1 - p0, p2 - p0)
            cross_product = cross(sub(p1, p0), sub(p2, p0))
            # normal = cross_product / np.linalg.norm(cross_product)
            magnitude = norm(cross_product)
            return [cross_product[0] / magnitude, cross_product[1] / magnitude,
       cross_product[2] / magnitude]

        But let's skip it for now. I can prob mock the normal for now

    */
    fr::face_3d laser_faces[] = {
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 1, 2, 0, 7),
        fr::face_3d(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 2, 1, 0, 3),
    };

    // Prepare model
    /* How to set it for render?

        constexpr model_3d_item(const bn::span<const vertex_3d> &vertices,
                            const bn::span<const face_3d> &faces,
                            const bn::color *palette)

    */

    bn::color laser_colors[] = {
        bn::color(24, 0, 0),
    };

    fr::model_3d_item laser_full(laser_vertices, laser_faces, laser_colors);

    // Do the actual render. Maybe a static one should be the best!

    if (static_count >= fr::constants_3d::max_static_models)
    {
        BN_LOG("Stage Section Renderer: reached static model max "
               "limit: " +
               bn::to_string<64>(fr::constants_3d::max_static_models));
        return static_count;
    }
    static_model_items[static_count] = &laser_full;
    return static_count + 1;
}
