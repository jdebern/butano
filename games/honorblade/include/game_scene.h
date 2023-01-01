#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "bn_optional.h"

namespace blade
{
	enum class scene_type
	{
		INTRO,
		SAVELOAD,
		WORLD,
	};

	class scene
	{

	public:
		virtual ~scene() = default;

		[[nodiscard]] virtual bn::optional<scene_type> update() = 0;

	protected:
		scene() = default;
	};

}

#endif
