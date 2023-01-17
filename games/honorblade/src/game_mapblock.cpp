#include "game_mapblock.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_fixed_point.h"

namespace blade
{
    void mapblock::init(const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item)
    {
        opt_bg_map_item = bn::regular_bg_map_item(vmap_cells[0], bn::size(vmap_columns, vmap_rows));
        
        if (opt_bg_map_item.has_value())
        {
            const bn::regular_bg_map_item& map_item = *opt_bg_map_item.get();
            opt_bg_item = bn::regular_bg_item(tiles_item, palette_item, map_item);
        }
    }

    void mapblock::load(bn::fixed_point& position, const unsigned short& source_tiles_ref)
    {
        bn::memory::copy(source_tiles_ref, vmap_cell_count, vmap_cells[0]);
        
        // Grab our background item ptr and create a new bg
        bn::regular_bg_item& bg_item_ptr = *opt_bg_item.get();
        opt_bg_ptr = bg_item_ptr.create_bg(position.x(), position.y());

        // Grab current pointers and update position
        bn::regular_bg_ptr& bg_ptr = *opt_bg_ptr.get();
        bg_ptr.set_position(position);
        
        bn::regular_bg_map_ptr bg_map_ptr = bg_ptr.map();
        bg_map_ptr.reload_cells_ref();
    }

    void mapblock::update()
    {

    }

    void mapblock::set_camera(bn::camera_ptr& camera)
    {
        bn::regular_bg_ptr& bg_ptr = *opt_bg_ptr.get();
        bg_ptr.set_camera(camera);
    }
}