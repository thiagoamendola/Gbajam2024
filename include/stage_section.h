#ifndef STAGE_H
#define STAGE_H

#include "static_model_3d_item.h"

class stage_section
{
  public:
    constexpr stage_section(
        const int starting_pos, const int ending_pos,
        const std::initializer_list<fr::model_3d_item> &static_model_items)
        : _static_model_items(static_model_items.begin()),
          _static_model_count(static_model_items.size()),
          _starting_pos(starting_pos), _ending_pos(ending_pos)
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

    constexpr const fr::model_3d_item *static_model_items() const
    {
        return _static_model_items;
    }

    constexpr const int static_model_count() const
    {
        return _static_model_count;
    }

  private:
    const fr::model_3d_item *_static_model_items;
    const int _static_model_count;
    int _starting_pos;
    int _ending_pos;
    // <-- Add dynamic_model_items
};

#endif