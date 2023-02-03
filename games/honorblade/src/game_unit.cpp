#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_assert.h"

#include "game_unit.h"
#include "game_data_enums.h"

namespace blade
{
    unit::unit()
    {

    }
    
    void unit::init(bn::sprite_item sprite)
    {
        opt_sprite_item = sprite;
        opt_sprite_ptr = opt_sprite_item->create_sprite(0, 0);
        opt_sprite_ptr->set_bg_priority((int)bg_priority::TERRAIN);
    }

    void unit::update()
    {
        if (opt_anim_action && !opt_anim_action->done())
        {
            opt_anim_action->update();
        }
    }
    
    void unit::set_position(bn::fixed x, bn::fixed y)
    {
        if (opt_sprite_ptr)
        {
            opt_sprite_ptr->set_position(x, y);
        }
    }

    void unit::set_position(const bn::fixed_point& point)
    {
        if (opt_sprite_ptr)
        {
            opt_sprite_ptr->set_position(point.x(), point.y());
        }
    }

    void unit::load_anim(int index)
    {
        if (anim_index == index) return;
        
        anim_index = index;
        opt_anim_action = anim_load_assets[index](this);
    }

    void unit::set_load_list(const load_unit_asset_t load_list[])
    {
        BN_ASSERT(load_list, "Must provide an asset load list");

        anim_load_assets = load_list;
    }
    void unit::set_camera(bn::camera_ptr camera)
    {
        if (opt_sprite_ptr)
        {
            opt_sprite_ptr->set_camera(camera);
        }
    }
}