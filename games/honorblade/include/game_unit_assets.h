#ifndef GAME_UNITASSETS_H
#define GAME_UNITASSETS_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"

namespace blade
{
    class unit;

    namespace unit_assets
    {
        [[nodiscard]] bn::sprite_animate_action<5> hero_load_anim(unit* unit);
    }
}

#endif