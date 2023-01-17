#include "game_scene_world.h"
#include "bn_log.h"
#include "bn_string.h"
#include "bn_fixed_point.h"

#include "common_variable_8x8_sprite_font.h"

#define WORLD_LOG_STATUS 0

namespace blade
{
	world::world()
		: text_generator(common::variable_8x8_sprite_font)
	{

#if WORLD_LOG_STATUS
		BN_LOG("Used_Alloc_EWRAM - ", bn::memory::used_alloc_ewram());
		BN_LOG("Available_alloc_EWRAM - ", bn::memory::available_alloc_ewram());
		bn::memory::log_alloc_ewram_status();

		BN_LOG("Used Stack IWRAM - ", bn::memory::used_stack_iwram());
		BN_LOG("Used Static IWRAM - ", bn::memory::used_static_iwram());
		BN_LOG("Used Static EWRAM - ", bn::memory::used_static_ewram());
#endif // WORLD_LOG_STATUS
	}

	bn::optional<scene_type> world::update()
	{
		map.update();

		text_sprites.clear();
		
		const bn::camera_ptr& camera = map.get_camera();
		bn::string<64> string;
		bn::ostringstream string_stream(string);
		string_stream << "Camera x:";
		string_stream << camera.position().x();
		string_stream << " y:";
		string_stream << camera.position().y();
		text_generator.generate(-100, -60, string, text_sprites);

		return scene_type::WORLD;
	}
}