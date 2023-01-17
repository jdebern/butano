#ifndef GAME_SCENE_WORLD
#define GAME_SCENE_WORLD

#include "game_scene.h"
#include "game_tilemap.h"

#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

namespace blade
{
	class world : public scene
	{
	public:
		world();

		[[nodiscard]] bn::optional<scene_type> update() final;

	protected:
		tilemap map;
		
		bn::sprite_text_generator		text_generator;
		bn::vector<bn::sprite_ptr, 32>	text_sprites;
	};
}

#endif