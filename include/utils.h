#include "bn_math.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"

constexpr bn::fixed_point unit_vector(bn::fixed_point original_vector)
{
    bn::fixed magnitude = bn::sqrt((original_vector.x() * original_vector.x()) + (original_vector.y() * original_vector.y()));
    magnitude = magnitude == 0 ? 1 : magnitude;
    return original_vector / magnitude;
}
