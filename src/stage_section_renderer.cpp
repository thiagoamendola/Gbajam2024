#include "stage_section_renderer.h"

#include "bn_log.h"
#include "bn_string.h"

// #include "fr_camera_3d.h"
// #include "fr_model_3d_item.h"
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
