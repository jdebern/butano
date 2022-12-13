
#include "bn_core.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_builder.h"

// map & bg includes
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"
#include "HonorbladeMap.h"

#include "common_fixed_8x8_sprite_font.h"
#include "common_fixed_8x16_sprite_font.h"

//#include "bn_regular_bg_items_test_bg.h"
#include "bn_regular_bg_tiles_map_palette.h"

namespace blade
{
    void test_scene()
    {
        bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
        text_generator.set_center_alignment();

        //bn::regular_bg_ptr test_bg_ptr = bn::regular_bg_items::test_bg.create_bg(50, 80);

        // map testing
        // Notes - tile maps are 8x8 pixel groupings called TILES
        // therefore, map tilesets need to be either 8x8 or multiples of it
        // 64x64 sets of 8x8 tiles in a 512x512 bmp
        bn::regular_bg_map_item background_layer_map_item(
            blade::Honormap_Background,
            bn::size(HONORMAP_LENGTH, HONORMAP_HEIGHT));

        bn::regular_bg_map_item objects_layer_map_item(
            blade::Honormap_Objects,
            bn::size(HONORMAP_LENGTH, HONORMAP_HEIGHT));
        
        bn::regular_bg_item background_bg_item(
            bn::regular_bg_items::map_palette.tiles_item(),
            bn::regular_bg_items::map_palette.palette_item(),
            map_item);
            
        bn::regular_bg_item objects_bg_item(
            bn::regular_bg_items::map_palette.tiles_item(),
            bn::regular_bg_items::map_palette.palette_item(),
            map_item);

        bn::regular_bg_ptr background_ptr = background_bg_item.create_bg(0, 0);
        bn::regular_bg_ptr objects_ptr = objects_bg_item.create_bg(0, 0);

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

    bn::bg_palettes::set_transparent_color(bn::color(16, 0, 16));

    while(true)
    {
        blade::test_scene();
        bn::core::update();
    }
}
