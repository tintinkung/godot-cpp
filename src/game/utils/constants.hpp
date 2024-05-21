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
        constexpr inline auto character_jump{ "character_jump" };
        constexpr inline auto body_entered{ "body_entered" };
        constexpr inline auto body_exited{ "body_exited" };
    }
}