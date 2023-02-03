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
        [[nodiscard]] bn::sprite_animate_action<10> load_hero_idle(unit* unit);
        [[nodiscard]] bn::sprite_animate_action<10> load_hero_move(unit* unit);
        
        [[nodiscard]] bn::sprite_animate_action<10> load_axe_idle(unit* unit);
        [[nodiscard]] bn::sprite_animate_action<10> load_axe_move(unit* unit);
        [[nodiscard]] bn::sprite_animate_action<10> load_axe_attack(unit* unit);

        const load_unit_asset_t hero_anims[] = {
            &load_hero_idle,    // idle
            &load_hero_move,    // move
            nullptr             // attack_1
        };

        const load_unit_asset_t axe_anims[] = {
            &load_axe_idle,
            &load_axe_move,
            &load_axe_attack
        };
    }
}

#endif