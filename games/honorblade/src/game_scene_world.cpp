#include "game_scene_world.h"
#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_fixed_point.h"
#include "bn_log.h"

#include "game_data_worldmap_large.h"
#include "bn_regular_bg_items_worldmap_tiles.h"

namespace blade
{
	static int current_screenblock = 0;
	static bn::array<uint8_t, 4> direction_frames;

	constexpr uint8_t north = 0;
	constexpr uint8_t south	= 1;
	constexpr uint8_t east	= 2;
	constexpr uint8_t west	= 3;
	constexpr uint8_t wait_frames = 0;
	constexpr uint8_t speed = 5;

	/*
	 auto used_alloc_ewram() -> int
		Returns the size in bytes of all allocated items in EWRAM with bn::memory::ewram_alloc, bn::memory::ewram_calloc and bn::memory::ewram_realloc.
	auto available_alloc_ewram() -> int
		Returns the number of bytes that still can be allocated in EWRAM with bn::memory::ewram_alloc, bn::memory::ewram_calloc and bn::memory::ewram_realloc.
	void log_alloc_ewram_status()
		Logs the current status of the EWRAM allocator.
	auto used_stack_iwram() -> int
		Returns the IWRAM used by the stack in bytes.
	auto used_static_iwram() -> int
		Returns the bytes of all static objects in IWRAM.
	auto used_static_ewram() -> int
		Returns the bytes of all static objects in EWRAM.
	*/

	world::world()
		: map_item(map_cells[0], bn::size(map_columns, map_rows))
		, map_background_item(bn::regular_bg_items::worldmap_tiles.tiles_item(), bn::regular_bg_items::worldmap_tiles.palette_item(), map_item)
		, background_ptr(map_background_item.create_bg(0, 0))
		, background_map_ptr(background_ptr.map())
	{
		bn::memory::copy(Worldmap_Large_Tiledata[0], map_cell_count, map_cells[0]);
		background_map_ptr.reload_cells_ref();

		//BN_LOG("Sizeof map: ", sizeof(Worldmap_Large_Tiledata));
		BN_LOG("Used_Alloc_EWRAM - ", bn::memory::used_alloc_ewram());
		BN_LOG("Available_alloc_EWRAM - ", bn::memory::available_alloc_ewram());
		bn::memory::log_alloc_ewram_status();

		BN_LOG("Used Stack IWRAM - ", bn::memory::used_stack_iwram());
		BN_LOG("Used Static IWRAM - ", bn::memory::used_static_iwram());
		BN_LOG("Used Static EWRAM - ", bn::memory::used_static_ewram());
	}

	bn::optional<scene_type> world::update()
	{
		if (bn::keypad::start_pressed())
		{
			if (0)
			{
				current_screenblock = (current_screenblock + 1) % 4;
				bn::memory::copy(Worldmap_Large_Tiledata[map_cell_count * current_screenblock], map_cell_count, map_cells[0]);
				background_map_ptr.reload_cells_ref();
				background_ptr.set_position(0, 0);
			}
			else
			{
				for (int x = 0; x < 32; x++)
				{
					for (int y = 0; y < 32; y++)
					{
						if ( x == 0 || y == 0 || x == 31 || y == 31)
						{
							bn::regular_bg_map_cell&		current_cell = map_cells[map_item.cell_index(x,y)];
							bn::regular_bg_map_cell_info	current_cell_info(current_cell);
							current_cell_info.set_tile_index( 0 );//1 + (x % 16));
							current_cell = current_cell_info.cell();
							background_map_ptr.reload_cells_ref();
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (direction_frames[i] > 0)
				direction_frames[i]--;
		}
		
		if (bn::keypad::up_held() && direction_frames[north] <= 0)
		{
			direction_frames[north] = wait_frames;
			background_ptr.set_y(background_ptr.position().y() + speed);
		}
		
		if (bn::keypad::down_held() && direction_frames[south] <= 0)
		{
			direction_frames[south] = wait_frames;
			background_ptr.set_y(background_ptr.position().y() - speed);
		}
		
		if (bn::keypad::right_held() && direction_frames[east] <= 0)
		{
			direction_frames[east] = wait_frames;
			background_ptr.set_x(background_ptr.position().x() - speed);
		}
		
		if (bn::keypad::left_held() && direction_frames[west] <= 0)
		{
			direction_frames[west] = wait_frames;
			background_ptr.set_x(background_ptr.position().x() + speed);
		}

		return scene_type::WORLD;
	}
}