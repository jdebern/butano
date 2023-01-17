
#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_log.h"
#include "bn_bg_maps.h"

#include "game_tilemap.h"
#include "game_data_worldmap_large.h"
#include "bn_regular_bg_items_worldmap_tiles.h"

#define MAP_LOG_STATUS 0

namespace blade
{
	static bn::array<uint8_t, 4> direction_frames;

	constexpr uint8_t north = 0;
	constexpr uint8_t south	= 1;
	constexpr uint8_t east	= 2;
	constexpr uint8_t west	= 3;
	constexpr uint8_t wait_frames = 0;
	constexpr uint8_t speed = 2;

    tilemap::tilemap()
        : opt_map_camera(bn::camera_ptr::create(0, 0)),
        opt_map_block(blade::mapblock()),
        opt_map_block_2(blade::mapblock())
    {
        bn::fixed_point map_pos(0,0);
        blade::mapblock& block = *opt_map_block.get();
        block.init(bn::regular_bg_items::worldmap_tiles.tiles_item(), bn::regular_bg_items::worldmap_tiles.palette_item());
        block.load(map_pos, Worldmap_Large_Tiledata[0]);
        block.set_camera(get_camera());
        
        map_pos.set_x(512);
        blade::mapblock& block_2 = *opt_map_block_2.get();
        block_2.init(bn::regular_bg_items::worldmap_tiles.tiles_item(), bn::regular_bg_items::worldmap_tiles.palette_item());
        block_2.load(map_pos, Worldmap_Large_Tiledata[1024]);
        block_2.set_camera(get_camera());

#if MAP_LOG_STATUS
        bn::bg_maps::log_status();        
#endif// MAP_LOG_STATUS
    }

    void tilemap::update()
    {
		for (int i = 0; i < 4; i++)
		{
			if (direction_frames[i] > 0)
				direction_frames[i]--;
		}
		
        bn::camera_ptr& camera = get_camera();
		if (bn::keypad::up_held() && direction_frames[north] <= 0)
		{
			direction_frames[north] = wait_frames;
            camera.set_y(camera.position().y() - speed);
		}
		
		if (bn::keypad::down_held() && direction_frames[south] <= 0)
		{
			direction_frames[south] = wait_frames;
            camera.set_y(camera.position().y() + speed);
		}
		
		if (bn::keypad::right_held() && direction_frames[east] <= 0)
		{
			direction_frames[east] = wait_frames;
            camera.set_x(camera.position().x() + speed);
		}
		
		if (bn::keypad::left_held() && direction_frames[west] <= 0)
		{
			direction_frames[west] = wait_frames;
            camera.set_x(camera.position().x() - speed);
		}
    }
}