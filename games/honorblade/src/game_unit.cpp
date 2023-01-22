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
        if (opt_anim_action)
        {
            opt_anim_action->update();
        }
    }
    
    void unit::set_position(bn::fixed& x, bn::fixed& y)
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

    // void unit::create_anim(int wait_updates, const bn::span<const uint16_t>& indices)
    // {
    //     BN_ASSERT(indices.size() >= 1 && indices.size() <= 5, "Invalid indices size");

    //     opt_anim_action = bn::sprite_animate_action<5>(
    //         *opt_sprite_ptr, wait_updates, opt_sprite_item->tiles_item(), true, indices);
    // }

    void unit::load_anim(load_unit_asset_t asset_func)
    {
        opt_anim_action = asset_func(this);
    }

    void unit::set_camera(bn::camera_ptr camera)
    {
        if (opt_sprite_ptr)
        {
            opt_sprite_ptr->set_camera(camera);
        }
    }
}