#ifndef GAME_SCENE_INTRO
#define GAME_SCENE_INTRO

#include "game_scene.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

namespace blade
{
	class intro : public scene
	{
	public:
		intro();

		[[nodiscard]] bn::optional<scene_type> update() final;
	
	protected:
		bn::sprite_text_generator		text_generator;
		bn::vector<bn::sprite_ptr, 32>	text_sprites;
	};
}

#endif