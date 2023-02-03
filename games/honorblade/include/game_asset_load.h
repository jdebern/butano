#ifndef GAME_ASSETLOAD_H
#define GAME_ASSETLOAD_H

#include "bn_sprite_animate_actions.h"

namespace blade
{
    typedef bn::sprite_animate_action<10> (*load_unit_asset_t)(class unit* unit);
}

#endif