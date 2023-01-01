#include "game_scene_world.h"
#include "game_data_worldmap.h"

#include "bn_bg_palette_items_map_palette.h"
#include "bn_regular_bg_items_map_tiles.h"

namespace blade
{
	world::world()
		: map_item(Worldmap_Tiledata[0], bn::size(map_columns, map_rows))
		, map_background_item(bn::regular_bg_items::map_tiles.tiles_item(), bn::regular_bg_items::map_tiles.palette_item(), map_item)
		, background_ptr(map_background_item.create_bg(8, 48))
		, background_map_ptr(background_ptr.map())
	{
		//bn::memory::clear(map_cell_count, map_cells[0]);

		//map_item = bn::regular_bg_map_item(Worldmap_Tiledata[0], bn::size(map_columns, map_rows));
		//map_background_item = bn::regular_bg_item(bn::regular_bg_items::map_tiles.tiles_item(), bn::regular_bg_items::map_tiles.palette_item(), map_item);
		// background_ptr = map_background_item.create_bg(8, 48);
		// background_map_ptr = background_ptr.map();
	}

	bn::optional<scene_type> world::update()
	{
		// Example --- Update cell info   
		// bn::regular_bg_map_cell&		current_cell = map_cells[map_item.cell_index(x, y)];
		// bn::regular_bg_map_cell_info	current_cell_info(current_cell);
		// current_cell_info.set_tile_index( indexID );//1 + (x % 16));
		// current_cell = current_cell_info.cell();
		// bg_map_ptr.reload_cells_ref();

		return scene_type::WORLD;
	}
}