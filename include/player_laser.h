#ifndef PLAYER_LASER_H
#define PLAYER_LASER_H

// #include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
// #include "fr_models_3d.h"
// #include "stage_section.h"

// #include "stage_section.h"

// #include "controller.h"
#include "player_ship.h"

class player_laser
{
  public:
    // static void render_single_section(
    //     const stage_section *section, fr::models_3d &models,
    //     const fr::model_3d_item **static_model_items);

    // static void render_sections(const bn::fixed camera_position,
    //                             stage_section_list_ptr sections,
    //                             size_t sections_count, fr::models_3d &models,
    //                             const fr::model_3d_item
    //                             **static_model_items);

    // static void manage_section_render(
    //     stage_section_list_ptr sections, size_t sections_count,
    //     fr::camera_3d &camera, fr::models_3d &models,
    //     );
    static int handle_player_laser(player_ship *_player_ship,
                                   const fr::model_3d_item **static_model_items,
                                   int static_count);

    static int render_player_laser(player_ship *_player_ship,
                                   const fr::model_3d_item **static_model_items,
                                   int static_count);
};

#endif
