#include "enemy_manager.h"

#include "bn_fixed.h"

#include "fr_models_3d.h"

#include "colliders.h"
#include "controller.h"

enemy_manager::enemy_manager(fr::models_3d *models, controller *controller)
    : _asteroid(fr::point_3d(6, 450, -10), fr::point_3d(0, 50, 0), models, controller)
{

}

void enemy_manager::destroy()
{
    _asteroid.destroy();
}

void enemy_manager::update()
{
    _asteroid.update();
}

int enemy_manager::statics_render(const fr::model_3d_item **static_model_items,
    int static_count)
{
    return _asteroid.statics_render(static_model_items, static_count);
}
