#include "bn_fixed.h"
#include "bn_fixed_point.h"

class controller
{
public:
    bn::fixed_point get_norm_directional();
    bn::fixed_point get_smooth_directional();

private:
    bn::fixed_point _previous_raw_dir_input;
    bn::fixed_point _smooth_dir_input;
    bn::fixed _interp;
};
