#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_log.h"
#include "bn_bg_maps.h"
#include "bn_algorithm.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_bg_palette_ptr.h"

#include "game_worldmap.h"
#include "game_data_enums.h"

// asset includes
#include "bn_affine_bg_items_landmass_warm.h"
#include "bn_regular_bg_items_water_tiles.h"
#include "bn_bg_palette_items_bg_palette.h"


#define MAP_LOG_STATUS 0

namespace blade
{
	constexpr uint8_t camera_speed = 1;

	worldmap::worldmap()
		: opt_map_camera(bn::camera_ptr::create(0,0))
	{
		create_terrain();
		create_water();
		//create_hero();

		// lookin at the castle
		//opt_map_camera->set_position(-200, -385);

		// lookin at second castle
		opt_map_camera->set_position(206, -255);
	}

	void worldmap::create_terrain()
	{
		opt_terrain_map_ptr = bn::affine_bg_items::landmass_warm.create_bg(0,0);
		opt_terrain_map_ptr->set_wrapping_enabled(false);
		opt_terrain_map_ptr->set_camera(opt_map_camera);
		opt_terrain_map_ptr->set_priority((int)bg_priority::TERRAIN);
		opt_terrain_map_ptr->set_z_order(0);
	}

	void worldmap::create_water()
	{
		for (int x = 0; x < water_cell_count; x++)
		{
           	water_cells[x] = (x % 6 == 0 ? 0x0005 : 0x0001);
		}
		opt_water_map_item = bn::regular_bg_map_item(water_cells[0], bn::size(water_rows, water_columns));
		opt_water_bg_item = bn::regular_bg_item(
			bn::regular_bg_items::water_tiles.tiles_item(),
			bn::regular_bg_items::water_tiles.palette_item(),
			*opt_water_map_item);

		opt_water_bg_ptr = opt_water_bg_item->create_bg(0,0);
		opt_water_bg_ptr->set_camera(opt_map_camera);
		opt_water_bg_ptr->set_priority((int)bg_priority::WATER);
		opt_water_bg_ptr->set_z_order(0);
	}

	// void worldmap::create_hero()
	// {
	// 	opt_hero_sprite_ptr = bn::sprite_items::hero_sprites.create_sprite(0, 0);
    //     opt_hero_sprite_ptr->set_tiles(bn::sprite_items::hero_sprites.tiles_item().create_tiles(0));
	// 	if (opt_hero_sprite_ptr)
	// 	{
	// 		hero_anim_action = bn::create_sprite_animate_action_forever(
    //                 *opt_hero_sprite_ptr, 5, bn::sprite_items::hero_sprites.tiles_item(), 1, 2, 3);
	// 	}

	// 	opt_hero_sprite_ptr->set_camera(opt_map_camera);
	// 	opt_hero_sprite_ptr->set_bg_priority((int)bg_priority::TERRAIN);
	// }

    void worldmap::update()
    {
		static uint8_t update_frames = 0;
		static uint8_t update_count = 0;

		update_frames++;
		if (update_frames > 5)
		{
			for (int x = 0; x < water_cell_count; x++)
			{
				if (x % 3 == 0)
				{
					water_cells[x] = bn::max(2, (water_cells[x] + 1) % 8);
				}
			}

			if (update_count % 2 == 0)
			{
				opt_water_bg_ptr->set_x(opt_water_bg_ptr->x() - 1);
			}

			bn::regular_bg_map_ptr map_ptr = opt_water_bg_ptr->map();
			map_ptr.reload_cells_ref();

			update_frames = 0;
			update_count++;
		}

        bn::camera_ptr camera = get_camera();
		bn::fixed_point cam_position = camera.position();

		if (bn::keypad::up_held())
		{
            cam_position.set_y(cam_position.y() - camera_speed);
		}
		else if (bn::keypad::down_held())
		{
            cam_position.set_y(cam_position.y() + camera_speed);
		}

		if (bn::keypad::right_held())
		{
            cam_position.set_x(cam_position.x() + camera_speed);
			//opt_hero_sprite_ptr->set_horizontal_flip(false);
		}
		else if (bn::keypad::left_held())
		{
            cam_position.set_x(cam_position.x() - camera_speed);
			//opt_hero_sprite_ptr->set_horizontal_flip(true);
		}

		// screen is 240 x 160
		cam_position.set_x(bn::clamp(cam_position.x(), bn::fixed(-392), bn::fixed(392)));
		cam_position.set_y(bn::clamp(cam_position.y(), bn::fixed(-432), bn::fixed(432)));
		camera.set_position(cam_position);
    }
}