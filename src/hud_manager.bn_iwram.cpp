#include "hud_manager.h"
#include "fr_camera_3d.h"
#include "fr_point_3d.h"
#include "bn_math.h"
#include "utils.h"

bn::fixed_point hud_manager::_compute_target_return()
{
    constexpr int focal_length_shift = fr::constants_3d::focal_length_shift;
    fr::point_3d target_world_pos = _player_ship->get_position();
    fr::point_3d cam_pos = _camera->position();
    fr::point_3d cam_u = _camera->u();
    fr::point_3d cam_v = _camera->v();

    bn::fixed depth_position = target_world_pos.y() - _player_ship->FOCUS_DISTANCE;
    bn::fixed depth_to_camera = _camera->position().y() - depth_position;

    int cam_x_i = cam_pos.x().integer();
    int cam_z_i = cam_pos.z().integer();
    int world_x_i = target_world_pos.x().integer();
    int world_z_i = target_world_pos.z().integer();
    int depth_to_camera_i = depth_to_camera.integer();

    int dir_x_i = cam_x_i + ((world_x_i << focal_length_shift) / depth_to_camera_i);
    int dir_z_i = cam_z_i - ((world_z_i << focal_length_shift) / depth_to_camera_i);

    int ux_i = cam_u.x().integer();
    int vx_i = cam_v.x().integer();
    int uz_i = cam_u.z().integer();
    int vz_i = cam_v.z().integer();
    int det = ux_i * vz_i - vx_i * uz_i;

    int sx_i = 0;
    int sy_i = 0;
    if(det != 0)
    {
        sx_i = (dir_x_i * vz_i - vx_i * dir_z_i) / det; // TODO: optimize division
        sy_i = (ux_i * dir_z_i - dir_x_i * uz_i) / det; // TODO: optimize division
    }

    bn::fixed_point rest_pos { int16_t(sx_i), int16_t(sy_i) };

    // Current position in screen space (sprite coordinates)
    bn::fixed_point current_pos(_target_spr.x(), _target_spr.y());
    bn::fixed_point dist_vec = rest_pos - current_pos;          // Remaining vector

    // Early out if already there
    if(dist_vec.x() == 0 && dist_vec.y() == 0)
    {
        return current_pos;
    }

    // Normalized direction vector (unit). Assumes unit_vector handles zero safely.
    bn::fixed_point norm_dist_vec = unit_vector(dist_vec);

    // Desired per-axis movement this frame:
    // min( remaining distance on that axis, TARGET_SPEED * |axis_unit_component| ) preserving sign.
    bn::fixed abs_dx = bn::abs(dist_vec.x());
    bn::fixed abs_dy = bn::abs(dist_vec.y());
    bn::fixed max_step_x = bn::abs(norm_dist_vec.x() * TARGET_SPEED);
    bn::fixed max_step_y = bn::abs(norm_dist_vec.y() * TARGET_SPEED);

    // Clamp so we don't exceed remaining distance.
    bn::fixed step_x = (abs_dx < max_step_x) ? abs_dx : max_step_x;
    bn::fixed step_y = (abs_dy < max_step_y) ? abs_dy : max_step_y;

    // Reapply original signs.
    if(dist_vec.x() < 0)
    {
        step_x = -step_x;
    }
    if(dist_vec.y() < 0)
    {
        step_y = -step_y;
    }

    bn::fixed_point new_pos(current_pos.x() + step_x, current_pos.y() + step_y);
    return new_pos;
}

bn::fixed_point hud_manager::_compute_target_move(const bn::fixed_point& dir_input)
{
    bn::fixed_point target_pos;
    target_pos.set_x(int(_target_spr.x() + dir_input.x() * TARGET_SPEED));
    target_pos.set_y(int(_target_spr.y() + dir_input.y() * TARGET_SPEED));

    if (target_pos.x() < TARGET_MIN_X)
    {
        target_pos.set_x(TARGET_MIN_X);
    }
    else if (target_pos.x() > TARGET_MAX_X)
    {
        target_pos.set_x(TARGET_MAX_X);
    }
    if (target_pos.y() < TARGET_MIN_Y)
    {
        target_pos.set_y(TARGET_MIN_Y);
    }
    else if (target_pos.y() > TARGET_MAX_Y)
    {
        target_pos.set_y(TARGET_MAX_Y);
    }

    return target_pos;
}