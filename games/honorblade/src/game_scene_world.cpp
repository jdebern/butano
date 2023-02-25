#include "bn_log.h"
#include "bn_string.h"
#include "bn_fixed_point.h"
#include "bn_bg_palettes.h"
#include "bn_color.h"
#include "bn_span.h"
#include "bn_common.h"
#include "bn_keypad.h"

#include "game_scene_world.h"
#include "game_data_enums.h"
#include "game_data_poi.h"
#include "game_unit_assets.h"

#include "common_variable_8x8_sprite_font.h"
#include "bn_sprite_items_hero_worldmap_unit.h"
#include "bn_sprite_items_axe_unit.h"

#define WORLD_LOG_STATUS 0

namespace blade
{
	world::world()
		: text_generator(common::variable_8x8_sprite_font)
	{
		bn::bg_palettes::set_transparent_color(bn::color(1,0,1));
		create_units();
		
		bn::camera_ptr camera = map.get_camera();
		blade::load_poi_asset();
		blade::opt_poi_ptr->set_position(208, -218);
		blade::opt_poi_ptr->set_camera(camera);

#if WORLD_LOG_STATUS
		BN_LOG("Used_Alloc_EWRAM - ", bn::memory::used_alloc_ewram());
		BN_LOG("Available_alloc_EWRAM - ", bn::memory::available_alloc_ewram());
		bn::memory::log_alloc_ewram_status();

		BN_LOG("Used Stack IWRAM - ", bn::memory::used_stack_iwram());
		BN_LOG("Used Static IWRAM - ", bn::memory::used_static_iwram());
		BN_LOG("Used Static EWRAM - ", bn::memory::used_static_ewram());
#endif // WORLD_LOG_STATUS
	}

	void world::create_units()
	{
		hero_unit.init(bn::sprite_items::hero_worldmap_unit);
		axe_unit.init(bn::sprite_items::axe_unit);

		hero_unit.set_load_list(unit_assets::hero_anims);
		hero_unit.load_anim(anim_indices::idle);

		axe_unit.set_load_list(unit_assets::axe_anims);
		axe_unit.load_anim(anim_indices::idle);

		bn::camera_ptr camera = map.get_camera();
		hero_unit.set_camera(camera);
		axe_unit.set_camera(camera);

		axe_unit.set_position(180, -215);
	}

	bn::optional<scene_type> world::update()
	{
		bn::camera_ptr camera = map.get_camera();
		bn::fixed_point old_cam_pos = camera.position();

		map.update();
		hero_unit.update();
		axe_unit.update();
		blade::opt_poi_action->update();

		bn::fixed_point new_cam_pos = camera.position();
		hero_unit.set_position(new_cam_pos);

		bn::sprite_ptr hero_sprite = hero_unit.get_sprite();

		if (old_cam_pos != new_cam_pos)
		{
			hero_unit.load_anim(anim_indices::move);
		}
		else
		{
			hero_unit.load_anim(anim_indices::idle);
		}

		if (old_cam_pos.x() < new_cam_pos.x())
		{
			hero_sprite.set_horizontal_flip(false);
		}
		else if (old_cam_pos.x() > new_cam_pos.x())
		{
			hero_sprite.set_horizontal_flip(true);
		}

		if (bn::keypad::b_pressed())
		{
			static int index = 0;
			index = (index + 1) % 3;
			axe_unit.load_anim(index);
		}

		text_sprites.clear();
		bn::string<64> string;
		bn::ostringstream string_stream(string);
		string_stream << "Camera x:";
		string_stream << new_cam_pos.x();
		string_stream << " y:";
		string_stream << new_cam_pos.y();
		text_generator.generate(-100, -60, string, text_sprites);
		text_generator.set_bg_priority((int)bg_priority::TOP);
		text_generator.set_z_order(0);
		

		return scene_type::WORLD;
	}
}