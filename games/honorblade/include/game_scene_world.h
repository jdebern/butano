#ifndef GAME_SCENE_WORLD
#define GAME_SCENE_WORLD

#include "game_scene.h"

#include "bn_core.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"

namespace blade
{
	class world : public scene
	{
	public:
		world();

		[[nodiscard]] bn::optional<scene_type> update() final;

	protected:
		static constexpr int map_rows = 32;
		static constexpr int map_columns = 32;
		static constexpr int map_cell_count = map_rows * map_columns;

		alignas(int) bn::regular_bg_map_cell map_cells[map_cell_count];
		bn::regular_bg_map_item		map_item;
		bn::regular_bg_item			map_background_item;
		bn::regular_bg_ptr			background_ptr;
		bn::regular_bg_map_ptr		background_map_ptr;
	};
}

#endif