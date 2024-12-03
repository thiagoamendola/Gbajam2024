#ifndef COLLIDERS_H
#define COLLIDERS_H

#include "bn_fixed.h"
#include "fr_point_3d.h"

struct sphere_collider
{
    fr::point_3d position;
    bn::fixed radius;

    constexpr sphere_collider(fr::point_3d _position, bn::fixed _radius)
        : position(_position), radius(_radius)
    {
    }
};

class base_collider
{
};

class sphere_collider_set : public base_collider
{
  public:
    constexpr sphere_collider_set(
        const bn::span<const sphere_collider> &sphere_colliders)
        : _sphere_collider_list(sphere_colliders)
    {
    }

  private:
    const bn::span<const sphere_collider> _sphere_collider_list;
};

#endif
