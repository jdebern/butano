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

namespace blade
{
    class unit
    {
		typedef bn::sprite_animate_action<5> (*load_unit_asset_t)(unit* unit);

        public:
            unit();
			void init(bn::sprite_item sprite);
			void set_camera(bn::camera_ptr camera);
			void set_position(bn::fixed& x, bn::fixed& y);
			void set_position(const bn::fixed_point& point);
			void load_anim(load_unit_asset_t asset_func);
            void update();

			inline bn::sprite_ptr get_sprite() { return *opt_sprite_ptr; }
			inline bn::sprite_item get_sprite_item() { return *opt_sprite_item; }

        private:
			bn::optional<bn::sprite_item> opt_sprite_item;
            bn::optional<bn::sprite_ptr> opt_sprite_ptr;
			bn::optional<bn::sprite_animate_action<5>> opt_anim_action;
    };
}

#endif