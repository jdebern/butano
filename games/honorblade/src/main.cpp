// core includes
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_builder.h"
#include "bn_timer.h"

// map & bg includes
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_bg_palette_ptr.h"
#include "bn_bg_palette_item.h"

// asset includes
#include "HonorbladeMap.h"
#include "common_fixed_8x8_sprite_font.h"
#include "common_fixed_8x16_sprite_font.h"
#include "bn_bg_palette_items_map_palette.h"
#include "bn_regular_bg_items_map_tiles.h"

namespace blade
{
	void map_test_scene()
	{
		bool bManualMap = true;
		if (bManualMap)
		{
			static constexpr int map_columns = 32;
			static constexpr int map_rows = 32;
			static constexpr int map_cell_count = map_columns * map_rows;

			// regular_bg_map_cell is a uint16_t typedef
			alignas(int) bn::regular_bg_map_cell map_cells[map_cell_count];
            bn::memory::clear(map_cell_count, map_cells[0]);

			bn::regular_bg_map_item map_item(
				//map_cells[0],
				Honormap_Background[0],
				bn::size(map_columns, map_rows));

			bn::regular_bg_item map_bg_item(
				bn::regular_bg_items::map_tiles.tiles_item(),
				bn::regular_bg_items::map_tiles.palette_item(),
				map_item);

			bn::regular_bg_ptr bg_ptr = map_bg_item.create_bg(8, 48);
			bn::regular_bg_map_ptr bg_map_ptr = bg_ptr.map();

			//bn::memory::copy(Honormap_Background[0], map_cell_count, map_cells[0]);
			//bg_map_ptr.reload_cells_ref();
		
			//bn::timer update_timer = bn::timer();

			int indexID = 1;
			// Remember! Stuff is only active when in scope.
			while(!bn::keypad::start_pressed())
			{
				if (bn::keypad::select_pressed())
				{
					for (int x = 0; x < map_rows; x++)
					{
						for (int y = 0; y < map_columns; y++ )
						{
							bn::regular_bg_map_cell&		current_cell = map_cells[map_item.cell_index(x, y)];
							bn::regular_bg_map_cell_info	current_cell_info(current_cell);
							current_cell_info.set_tile_index( indexID );//1 + (x % 16));
							current_cell = current_cell_info.cell();
						}
					}

					indexID++;
					bg_map_ptr.reload_cells_ref();
					//update_timer.restart();
				}


				bn::core::update();
			}
		}
		else
		{
			//bn::regular_bg_ptr test_bg_ptr = bn::regular_bg_items::test_bg.create_bg(50, 80);
			//bn::bg_palette_ptr bg_palette = bn::bg_palette_items::map_palette.create_palette();

			// map testing
			// Notes - tile maps are 8x8 pixel groupings called TILES
			// therefore, map tilesets need to be either 8x8 or multiples of it
			// 64x64 sets of 8x8 tiles in a 512x512 bmp
			bn::regular_bg_map_item background_layer_map_item(
				blade::Honormap_Background[0],
				bn::size(HONORMAP_LENGTH, HONORMAP_HEIGHT));

			// bn::regular_bg_map_item objects_layer_map_item(
			//     blade::Honormap_Objects[0],
			//     bn::size(HONORMAP_LENGTH, HONORMAP_HEIGHT));
			
			bn::regular_bg_item background_bg_item(
				bn::regular_bg_items::map_tiles.tiles_item(),
				bn::bg_palette_items::map_palette,
				background_layer_map_item);
				
			// bn::regular_bg_item objects_bg_item(
			//     bn::regular_bg_items::map_tiles.tiles_item(),
			//     bn::regular_bg_items::map_tiles.palette_item(),
			//     objects_layer_map_item);

			bn::regular_bg_ptr background_ptr = background_bg_item.create_bg(0, 0);
			//bn::regular_bg_ptr objects_ptr = objects_bg_item.create_bg(0, 0);

			bn::regular_bg_map_ptr bg_map_ptr = background_ptr.map();
			bg_map_ptr.reload_cells_ref();

			// Remember! Stuff is only active when in scope.
			while(!bn::keypad::start_pressed())
			{
				bn::core::update();
			}
		}
		
	}

	void text_test_scene()
	{
		bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
		text_generator.set_center_alignment();

		bn::vector<bn::sprite_ptr, 32> text_sprites;
		text_generator.generate(0, -14, "Testing grid maps", text_sprites);
		text_generator.generate(0, 24, "[Press Start]", text_sprites);

		while(!bn::keypad::start_pressed())
		{
			bn::core::update();
		}
	}
}

int main()
{
	bn::core::init();

	//bn::bg_palettes::set_transparent_color(bn::color(16, 0, 16));

	while(true)
	{
		blade::text_test_scene();
		bn::core::update();
		blade::map_test_scene();
		bn::core::update();
	}
}
