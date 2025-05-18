#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "fr_models_3d.h"

#include "controller.h"
#include "asteroid.h"

class enemy_manager
{
public:
    enemy_manager(fr::models_3d *models, controller *controller);

    void destroy();

    void update(); 

    int statics_render(const fr::model_3d_item **static_model_items,
      int static_count);

    asteroid _asteroid;

// private:
    
};

#endif
