#include "game_unit.h"
#include "game_unit_assets.h"

namespace blade
{
    namespace unit_assets
    {
        [[nodiscard]] bn::sprite_animate_action<10> load_hero_move(unit* unit)
        {
            return bn::create_sprite_animate_action_forever(
                        unit->get_sprite(), 5, unit->get_sprite_item().tiles_item(),
                        4, 5, 6, 7);
        }

        [[nodiscard]] bn::sprite_animate_action<10> load_hero_idle(unit* unit)
        {
            return bn::create_sprite_animate_action_forever(
                        unit->get_sprite(), 12, unit->get_sprite_item().tiles_item(),
                        0, 1, 0, 1, 2, 3);
        }
        
        [[nodiscard]] bn::sprite_animate_action<10> load_axe_move(unit* unit)
        {
            return bn::create_sprite_animate_action_forever(
                        unit->get_sprite(), 5, unit->get_sprite_item().tiles_item(),
                        3, 4, 5);
        }

        [[nodiscard]] bn::sprite_animate_action<10> load_axe_idle(unit* unit)
        {
            return bn::create_sprite_animate_action_forever(
                        unit->get_sprite(), 8, unit->get_sprite_item().tiles_item(),
                        0, 1, 2, 2, 2, 1, 0, 0, 0);
        }

        [[nodiscard]] bn::sprite_animate_action<10> load_axe_attack(unit* unit)
        {
            return bn::create_sprite_animate_action_once(
                        unit->get_sprite(), 10, unit->get_sprite_item().tiles_item(),
                        6, 7, 8, 8);
        }
    }
}