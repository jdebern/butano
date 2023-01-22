#include "game_unit.h"
#include "game_unit_assets.h"

namespace blade
{
    namespace unit_assets
    {
        [[nodiscard]] bn::sprite_animate_action<5> hero_load_anim(unit* unit)
        {
            return bn::create_sprite_animate_action_forever(
                        unit->get_sprite(), 5, unit->get_sprite_item().tiles_item(), 1, 2, 3);
        }
    }
}