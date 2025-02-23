
#include "bn_core.h"
#include "bn_memory.h"
// #include "bn_keypad.h"
// #include "bn_sprite_position_hbe_ptr.h"
// #include "bn_fixed.h"
// #include "bn_fixed_point.h"
// #include "bn_sprite_text_generator.h"
// #include "bn_sprite_ptr.h"
// #include "bn_bg_palettes.h"
// #include "bn_bg_palettes_actions.h"
// #include "bn_colors.h"
// #include "bn_sprite_animate_actions.h"
// #include "bn_regular_bg_ptr.h"
// #include "bn_display.h"
// #include "bn_math.h"
// #include "common_variable_8x16_sprite_font.h"

#include "fr_common_stuff.h"
#include "scene_type.h"
// #include "fr_jam_intro_scene.h"
#include "fr_butano_intro_scene.h"

#include "test_3d_scene.h"
#include "test_butano_scene.h"
#include "title_scene.h"

#include "bn_regular_bg_items_floor.h"
#include "bn_sprite_items_arrow.h"
#include "bn_sprite_items_controller.h"
#include "bn_sprite_items_ninja.h"

#if FR_PROFILE
#include "bn_log.h"
#endif

int main()
{
#if FR_PROFILE
    // constexpr const char *profile_keys =
    //     "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    //     "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010A0A0A0A0A0A0A0"
    //     "A0A0A0A0A0A01010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111111111101010101010101010101010101010101010101010"
    //     "1010A0A0A0A0A0A01010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A01010101010101010101010101010101010101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010"
    //     "10A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010A0A0A0A0A010101010101010101818181818181818A8A8A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0101010101010101010101010101010101010101010101010101010"
    //     "101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010101010101010101011111111111111111111111111111111111111111111111110101010101010101010101010101010101111111111111111111111111111111111111111111111111111111111111111111111"
    //     "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110101010101010101010101010111111111111111111111111111111111111111111111111111111101010101010101010101010101010101111111111111110"
    //     "1010101010101010101010101010101010101010101010101010111111111111111110101010101010101010101010101010101010101010101010101011111111111111111111111010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010A0A0"
    //     "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0"
    //     "A0A0A0A0A0A0A0A0A0A0A0A010101010101010101010101010101010101010101010101010181818181818181818181810101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111111111111111111111111111"
    //     "1110101010101010101010101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010101010A0A0A0A0A0A0A0A0101010101010101010A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A01010101010101010A0A0A0A0A0A0"
    //     "A0A0A0A0A0A010101010101010101010101010101010101010101010101010101010101010101010101010101010101011111111101010101010101010101010101010101010101010101011111111101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010101010101010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010101010101010101010101010101010101010101010101010101010"
    //     "10101010101010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    // bn::core::init(profile_keys);
    bn::core::init();

    BN_LOG("iwram: ", bn::memory::used_static_iwram());
    BN_LOG("ewram: ", bn::memory::used_static_ewram());

    bn::optional<scene_type> next_scene = scene_type::TITLE;

#else
    bn::core::init();
    bn::optional<scene_type> next_scene = scene_type::BUTANO_INTRO;

#endif

    bn::unique_ptr<fr::common_stuff> common_stuff(new fr::common_stuff());
    bn::unique_ptr<fr::scene> scene;

    while (true)
    {
        if (scene)
        {
            next_scene = scene->update();
        }

        if (next_scene)
        {
            if (scene)
            {
                scene.reset();
            }
            else
            {
                switch (*next_scene)
                {

                case scene_type::TEST_BUTANO:
                    scene.reset(new test_butano_scene());
                    break;

                case scene_type::BUTANO_INTRO:
                    scene.reset(new fr::butano_intro_scene(*common_stuff));
                    break;

                case scene_type::TEST_3D:
                    scene.reset(new test_3d_scene());
                    break;

                case scene_type::TITLE:
                    scene.reset(new title_scene());
                    break;

                default:
                    BN_ERROR("Invalid next scene: ", int(*next_scene));
                    break;
                }
            }
        }

        common_stuff->update();
        bn::core::update();
    }
    //         test_butano_scene.update(); // <-- Remove later

    //         bn::core::update();
    //     }

    //     // TEST 3D SCENE

    //     // scene.reset(new test_butano_scene());
    //     // next_scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();

    //     // while (!next_scene)
    //     // {
    //     //     next_scene = scene->update();
    //     //     common_stuff->update();
    //     //     bn::core::update();
    //     // }

    //     // scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();

    //     // // BUTANO INTRO
    //     // scene.reset(new fr::butano_intro_scene(*common_stuff));
    //     // next_scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();

    //     // while (!next_scene)
    //     // {
    //     //     next_scene = scene->update();
    //     //     common_stuff->update();
    //     //     bn::core::update();
    //     // }

    //     // scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();

    //     // // GBA JAM INTRO
    //     // scene.reset(new fr::jam_intro_scene());
    //     // next_scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();

    //     // while (!next_scene)
    //     // {
    //     //     next_scene = scene->update();
    //     //     common_stuff->update();
    //     //     bn::core::update();
    //     // }

    //     // scene.reset();
    //     // common_stuff->update();
    //     // bn::core::update();
    // }
}
