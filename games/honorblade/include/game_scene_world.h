#ifndef GAME_SCENE_WORLD
#define GAME_SCENE_WORLD

#include "game_scene.h"
#include "game_worldmap.h"
#include "game_unit.h"

#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

namespace blade
{
	class world : public scene
	{
	public:
		world();

		void create_hero();

		[[nodiscard]] bn::optional<scene_type> update() final;

	protected:
		worldmap map;
		unit hero_unit;
		
		bn::sprite_text_generator		text_generator;
		bn::vector<bn::sprite_ptr, 32>	text_sprites;
	};
}

#endif