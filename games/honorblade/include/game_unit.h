#ifndef GAME_UNIT_H
#define GAME_UNIT_H

#include "bn_common.h"
#include "bn_fixed_point.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_span.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "game_asset_load.h"
#include "game_unit_assets.h"

namespace blade
{
	enum anim_indices
	{
		idle = 0,
		move,
		attack_1,

		total
	};
    
	class unit
    {
        public:
            unit();
			void init(bn::sprite_item sprite);
			void set_camera(bn::camera_ptr camera);
			void set_position(bn::fixed x, bn::fixed y);
			void set_position(const bn::fixed_point& point);
			void load_anim(int index);
			void set_load_list(const load_unit_asset_t load_list[]);
            void update();

			inline bn::sprite_ptr get_sprite() { return *opt_sprite_ptr; }
			inline bn::sprite_item get_sprite_item() { return *opt_sprite_item; }

        private:
			bn::optional<bn::sprite_item> opt_sprite_item;
            bn::optional<bn::sprite_ptr> opt_sprite_ptr;
			bn::optional<bn::sprite_animate_action<10>> opt_anim_action;

			const load_unit_asset_t* anim_load_assets;

			int anim_index = -1;
    };
}

#endif // GAME_UNIT_H