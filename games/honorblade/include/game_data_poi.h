#ifndef GAME_DATA_POI_H
#define GAME_DATA_POI_H

#include "bn_common.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "game_data_enums.h"

// asset includes
#include "bn_sprite_items_poi.h"

namespace blade
{
    const int poi_name_size = 25;

    bn::optional<bn::sprite_ptr> opt_poi_ptr;
    bn::optional<bn::sprite_animate_action<10>> opt_poi_action;

    struct poi_t
    {
        uint8_t mapid;
        uint8_t x;
        uint8_t y;

        char name[poi_name_size];
    };

    void load_poi_asset()
    {
        opt_poi_ptr = bn::sprite_items::poi.create_sprite(0, 0);
        opt_poi_ptr->set_bg_priority((int)bg_priority::TERRAIN);
        opt_poi_action = bn::create_sprite_animate_action_forever(
			*opt_poi_ptr,
			3,
			bn::sprite_items::poi.tiles_item(),
			0,1,2,3,4,5,6,7,8,9);
    }
}

#endif // GAMEDATA_POI_H