#ifndef _GAME_MAPBLOCK_H
#define _GAME_MAPBLOCK_H

#include "bn_core.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_tiles_item.h"
#include "bn_bg_palette_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_fixed_point.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"

namespace blade
{
    class mapblock
    {
        public:
            void init(const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item);
            void update();
			void set_camera(bn::camera_ptr& camera);
            void load(bn::fixed_point& position, const unsigned short& source_tiles_ref);

        protected:
            static constexpr int vmap_rows = 32;
            static constexpr int vmap_columns = 32;
            static constexpr int vmap_cell_count = vmap_rows * vmap_columns;

            alignas(int) bn::regular_bg_map_cell	vmap_cells[vmap_cell_count];
            bn::optional<bn::regular_bg_map_item>	opt_bg_map_item;
            bn::optional<bn::regular_bg_item>		opt_bg_item;
            bn::optional<bn::regular_bg_ptr>		opt_bg_ptr;
    };
}


#endif