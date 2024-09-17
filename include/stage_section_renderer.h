#ifndef STAGE_SECTION_RENDERER_H
#define STAGE_SECTION_RENDERER_H

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"
#include "stage_section.h"

#include "stage_section.h"

class stage_section_renderer
{
  public:
    static void render_single_section(
        const stage_section *section, fr::models_3d &_models,
        const fr::model_3d_item **_static_model_items);

    static void manage_section_render(
        stage_section_list_ptr sections, size_t sections_count,
        fr::camera_3d &_camera, fr::models_3d &_models,
        const fr::model_3d_item **_static_model_items);
};

#endif
