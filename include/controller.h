#include "bn_fixed.h"
#include "bn_fixed_point.h"

class Controller
{
public:
    bn::fixed_point get_norm_directional();
    bn::fixed_point get_smooth_directional();

private:
    bn::fixed_point previous_raw_dir_input;
    bn::fixed_point smooth_dir_input;
    bn::fixed interp;
};
