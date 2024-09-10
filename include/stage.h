#ifndef STAGE_H
#define STAGE_H

#include "static_model_3d_item.h"

struct stage_section
{
    int _starting_pos;
    int _ending_pos;
    const fr::model_3d_item *_static_model_items;
    // <-- Add dynamic_model_items

    constexpr stage_section(const int starting_pos, const int ending_pos,
                            const fr::model_3d_item *static_model_items)
        : _starting_pos(starting_pos), _ending_pos(ending_pos),
          _static_model_items(static_model_items)
    {
    }

    constexpr int starting_pos()
    {
        return _starting_pos;
    }

    constexpr int ending_pos()
    {
        return _ending_pos;
    }

    constexpr const fr::model_3d_item *static_model_items()
    {
        return _static_model_items;
    }
};

#endif