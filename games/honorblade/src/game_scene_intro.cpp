#include "game_scene_intro.h"
#include "bn_keypad.h"

#include "common_fixed_8x8_sprite_font.h"

namespace blade
{
    intro::intro()
        : text_generator(common::fixed_8x8_sprite_font)
    {
        text_generator.set_center_alignment();
        
		text_generator.generate(0, -14, "H o n o r - B l a d e", text_sprites);
		text_generator.generate(0, 24, "[Press Start]", text_sprites);
    }

    bn::optional<scene_type> intro::update()
    {
        if (bn::keypad::start_pressed())
            return scene_type::WORLD;
        
        return scene_type::INTRO;
    }
}