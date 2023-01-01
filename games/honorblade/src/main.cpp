// core includes
#include "bn_core.h"

#include "game_scene_intro.h"
#include "game_scene_world.h"

int main()
{
	bn::core::init();

	bn::unique_ptr<blade::scene> game_scene;
	bn::optional<blade::scene_type> current_scene = blade::scene_type::WORLD;
	bn::optional<blade::scene_type> next_scene;
	
	game_scene.reset(new blade::intro());

	while(true)
	{
		next_scene = game_scene->update();
		if (next_scene && next_scene != current_scene)
		{
			switch (*next_scene)
			{
				case blade::scene_type::WORLD:
					game_scene.reset(new blade::world());
				break;

				default:
					game_scene.reset(new blade::intro());
				break;
			}

			current_scene = next_scene;
		}

		bn::core::update();
	}
}
