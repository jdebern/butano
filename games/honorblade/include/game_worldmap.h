#ifndef GAME_WORLDMAP
#define GAME_WORLDMAP

#include "bn_core.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"

#include "bn_affine_bg_map_item.h"
#include "bn_affine_bg_item.h"
#include "bn_affine_bg_ptr.h"

#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"

namespace blade
{
    class worldmap
    {

        public:
            worldmap();

            void update();
			
			[[nodiscard]] bn::camera_ptr get_camera() { return *opt_map_camera; }

        protected:
			void create_terrain();
			void create_water();
            //void create_hero();

            static constexpr int water_rows = 32;
            static constexpr int water_columns = 32;
            static constexpr int water_cell_count = water_rows * water_columns;
            alignas(int) bn::regular_bg_map_cell	water_cells[water_cell_count];

            bn::optional<bn::regular_bg_map_item>	opt_water_map_item;
            bn::optional<bn::regular_bg_item>		opt_water_bg_item;
            bn::optional<bn::regular_bg_ptr>		opt_water_bg_ptr;

			bn::optional<bn::affine_bg_item>		opt_terrain_map_bg_item;
			bn::optional<bn::affine_bg_ptr>			opt_terrain_map_ptr;

            bn::optional<bn::camera_ptr>			opt_map_camera;
    };
}

#endif