#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_log.h"
#include "bn_bg_maps.h"
#include "bn_algorithm.h"
#include "bn_fixed_point.h"
//#include "bn_affine_bg_map_cell_info.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_bg_palette_ptr.h"

#include "game_tilemap.h"
#include "game_data_enums.h"

//#include "bn_sprite_items_water_tile_warm.h"
#include "bn_affine_bg_items_landmass_warm.h"
#include "bn_regular_bg_items_water_tiles.h"
#include "bn_bg_palette_items_bg_palette.h"


#define MAP_LOG_STATUS 0

namespace blade
{
	constexpr uint8_t camera_speed = 2;

	tilemap::tilemap()
		: opt_map_camera(bn::camera_ptr::create(0,0))
	{
		create_terrain();
		create_water();

		// lookin at the castle
		//opt_map_camera->set_position(-200, -385);

		// lookin at second castle
		opt_map_camera->set_position(206, -255);
	}

	void tilemap::create_terrain()
	{
		opt_terrain_map_ptr = bn::affine_bg_items::landmass_warm.create_bg(0,0);
		//opt_terrain_map_ptr->set_palette(bn::affine_bg_items::landmass_warm.palette_item().create_palette());
		//opt_terrain_map_ptr->set_palette(bn::bg_palette_items::bg_palette.create_palette());
		opt_terrain_map_ptr->set_wrapping_enabled(false);
		opt_terrain_map_ptr->set_camera(opt_map_camera);
		opt_terrain_map_ptr->set_priority((int)bg_priority::TERRAIN);
		opt_terrain_map_ptr->set_z_order(0);
	}
	
	void tilemap::create_water()
	{
#if 0
		opt_water_sprite = bn::sprite_items::water_tile_warm.create_sprite(0, 0);
		opt_water_sprite->set_bg_priority((int)bg_priority::WATER);
		opt_water_sprite->set_scale(6.0);
#else
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
		//opt_water_bg_ptr->set_wrapping_enabled(true);
		opt_water_bg_ptr->set_camera(opt_map_camera);
		opt_water_bg_ptr->set_priority((int)bg_priority::WATER);
		opt_water_bg_ptr->set_z_order(0);
#endif
	}

    void tilemap::update()
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
		}
		else if (bn::keypad::left_held())
		{
            cam_position.set_x(cam_position.x() - camera_speed);
		}

		// screen is 240 x 160 
		cam_position.set_x(bn::clamp(cam_position.x(), bn::fixed(-392), bn::fixed(392)));
		cam_position.set_y(bn::clamp(cam_position.y(), bn::fixed(-432), bn::fixed(432)));
		camera.set_position(cam_position);
    }
}