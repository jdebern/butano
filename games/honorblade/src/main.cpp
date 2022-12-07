
#include "bn_core.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_builder.h"

#include "common_fixed_8x8_sprite_font.h"
#include "common_fixed_8x16_sprite_font.h"

#include "bn_regular_bg_items_test_bg.h"

namespace blade
{
    void test_scene()
    {
        bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
        text_generator.set_center_alignment();

        bn::regular_bg_ptr test_bg_ptr = bn::regular_bg_items::test_bg.create_bg(50, 80);

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -14, "Testing sprite sizes", text_sprites);
        text_generator.generate(0, 24, "Bottom Text", text_sprites);

        while(!bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    while(true)
    {
        blade::test_scene();
        bn::core::update();
    }
}
