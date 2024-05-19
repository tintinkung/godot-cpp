#pragma once

#include <cstdint>
#include <string>

namespace ling::inline constants
{

    namespace event
    {
        constexpr inline auto position_changed{ "position_changed" };
        constexpr inline auto entered_area{ "entered_area" };
        constexpr inline auto exited_area{ "exited_area" };
        constexpr inline auto spawn_projectile{ "spawn_projectile" };
        constexpr inline auto character_move{ "character_move" };
        constexpr inline auto character_rotate{ "character_rotate" };
        constexpr inline auto character_shoot{ "character_shoot" };
        constexpr inline auto body_entered{ "body_entered" };
        constexpr inline auto body_exited{ "body_exited" };
    }

    namespace action
    {
        constexpr inline auto move_left{ "move_left" };
        constexpr inline auto move_right{ "move_right" };
        constexpr inline auto move_up{ "move_up" };
        constexpr inline auto move_down{ "move_down" };
        constexpr inline auto shoot{ "shoot" };
    }
}