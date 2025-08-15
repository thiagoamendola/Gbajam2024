#include "player_laser.h"

#include "bn_colors.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_constants_3d.h"
#include "fr_model_3d_item.h"
#include "fr_sin_cos.h"

player_laser::player_laser()
    : laser_full(laser_vertices, laser_faces, fr::model_3d_items::laser_colors)
{
}

void player_laser::handle_player_laser()
{
    render_laser = false;
    if (bn::keypad::a_held())
    {
        render_laser = true;
        // <-- Move the laser sound here
        // <-- We can also do some smarter checks for laser cadency
        // <-- Also check for collision
    }
}

int player_laser::render_player_laser(
    fr::point_3d player_ship_pos, bn::fixed psi, bn::fixed phi,
    const fr::model_3d_item **static_model_items, int static_count)
{
    if (render_laser)
    {
        int phi_raw = phi.right_shift_integer();
        int psi_raw = psi.right_shift_integer();

        // Calculate laser trajectory.
        fr::point_3d forward_vec = fr::point_3d(0, -200, 0); // <-- magic number
        // use magnitude instead???
        forward_vec.set_x(-forward_vec.y() * fr::sin(phi_raw));
        forward_vec.set_y(forward_vec.y());
        forward_vec.set_z(-forward_vec.y() * fr::cos(psi_raw));

        // Update vertices.
        //<-- Make const for these points for easy changing later
        laser_vertices[0].reset(player_ship_pos + fr::point_3d(10, 0, 2)); // <-- magic numbers
        laser_vertices[1].reset(player_ship_pos + fr::point_3d(10, 0, -2));
        laser_vertices[2].reset(player_ship_pos + forward_vec);
        laser_vertices[3].reset(player_ship_pos + fr::point_3d(-10, 0, 2));
        laser_vertices[4].reset(player_ship_pos + fr::point_3d(-10, 0, -2));
        laser_vertices[5].reset(player_ship_pos + forward_vec);

        // Update faces.
        laser_faces[0].reset(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 1, 2, 0,
                             7);
        laser_faces[1].reset(laser_vertices, fr::vertex_3d(0, 1, 0), 0, 2, 1, 0,
                             7);
        laser_faces[2].reset(laser_vertices, fr::vertex_3d(0, 1, 0), 3, 4, 5, 0,
                             7);
        laser_faces[3].reset(laser_vertices, fr::vertex_3d(0, 1, 0), 3, 5, 4, 0,
                             7);

        // Add nem mesh as static object
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
    return static_count;
}
