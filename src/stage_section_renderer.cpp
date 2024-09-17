#include "stage_section_renderer.h"

#include "stage_section.h"

#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_string.h"

#include "fr_camera_3d.h"
#include "fr_model_3d_item.h"
#include "fr_models_3d.h"

#include "stage_section.h"

void stage_section_renderer::render_single_section(
    const stage_section *section, fr::models_3d &models,
    const fr::model_3d_item **static_model_items)
{
    const int static_model_count = section->static_model_count();
    BN_LOG("STATICS SIZE: " + bn::to_string<32>(static_model_count));

    // <-- If new section has less models, we might run into an issue
    for (int i = 0; i < static_model_count; i++)
    {
        static_model_items[i] = &section->static_model_items()[i];
    }

    models.set_static_model_items(static_model_items, static_model_count);
}

void stage_section_renderer::manage_section_render(
    stage_section_list_ptr sections, size_t sections_count,
    fr::camera_3d &_camera, fr::models_3d &_models,
    const fr::model_3d_item **_static_model_items)
{
    // - Create stage_section_render
    // - it should have a render_section(section) with the imediate code
    // below
    // - later, make it start rendering only if camera is below starting_pos
    // - Make it stop rendering if camera is below ending_pos
    // - Create another section so we can test some more partial renders
    // - For now, iterate through all sections in list. We can do something
    // smarter later.

    const bn::fixed camera_position = _camera.position().y();
    BN_LOG("CAMERA POS: " + bn::to_string<32>(camera_position));

    stage_section_renderer::render_single_section(sections[0], _models,
                                                  _static_model_items);

    // Final models update
    _models.update(_camera);
}