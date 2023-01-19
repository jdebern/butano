#include "bn_keypad.h"
#include "bn_array.h"
#include "bn_log.h"
#include "bn_bg_maps.h"
#include "bn_algorithm.h"
#include "bn_fixed_point.h"
#include "game_tilemap.h"
#include "game_data_worldmap_affine.h"

#include "bn_affine_bg_items_landmass_warm.h"

#define MAP_LOG_STATUS 0

namespace blade
{
	static bn::array<uint8_t, 4> direction_frames;

	constexpr uint8_t north = 0;
	constexpr uint8_t south	= 1;
	constexpr uint8_t east	= 2;
	constexpr uint8_t west	= 3;
	constexpr uint8_t wait_frames = 0;
	constexpr uint8_t speed = 5;

	tilemap::tilemap()
		: opt_map_camera(bn::camera_ptr::create(0,0))
	{
		opt_map_ptr = bn::affine_bg_items::landmass_warm.create_bg(0,0);
		opt_map_ptr->set_wrapping_enabled(false);
		opt_map_ptr->set_camera(opt_map_camera);
		opt_map_camera->set_position(-200, -385);
		
	}

    void tilemap::update()
    {
		for (int i = 0; i < 4; i++)
		{
			if (direction_frames[i] > 0)
				direction_frames[i]--;
		}
		
        bn::camera_ptr& camera = get_camera();
		bn::fixed_point cam_position = camera.position();

		if (bn::keypad::up_held() && direction_frames[north] <= 0)
		{
			direction_frames[north] = wait_frames;
            cam_position.set_y(cam_position.y() - speed);
		}
		
		if (bn::keypad::down_held() && direction_frames[south] <= 0)
		{
			direction_frames[south] = wait_frames;
            cam_position.set_y(cam_position.y() + speed);
		}
		
		if (bn::keypad::right_held() && direction_frames[east] <= 0)
		{
			direction_frames[east] = wait_frames;
            cam_position.set_x(cam_position.x() + speed);
		}
		
		if (bn::keypad::left_held() && direction_frames[west] <= 0)
		{
			direction_frames[west] = wait_frames;
            cam_position.set_x(cam_position.x() - speed);
		}

		// screen is 240 x 160 
		cam_position.set_x(bn::clamp(cam_position.x(), bn::fixed(-392), bn::fixed(392)));
		cam_position.set_y(bn::clamp(cam_position.y(), bn::fixed(-432), bn::fixed(432)));
		camera.set_position(cam_position);
    }
}