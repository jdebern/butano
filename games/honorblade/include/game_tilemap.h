#ifndef _GAME_TILEMAP
#define _GAME_TILEMAP

#include "bn_core.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"
#include "bn_affine_bg_ptr.h"

namespace blade
{
    class tilemap
    {

        public:
            tilemap();

            void update();

			[[nodiscard]] bn::camera_ptr& get_camera() { return *opt_map_camera.get(); }

        protected:
			bn::optional<bn::affine_bg_ptr> opt_map_ptr;
            bn::optional<bn::camera_ptr>	opt_map_camera;
    };
}

#endif