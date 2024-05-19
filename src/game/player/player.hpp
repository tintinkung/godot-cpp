#pragma once

#include "./control/character.hpp"

namespace ling
{
    class Player : public Character
    {
        GDCLASS(Player, Character)

    public:
        Player();
        ~Player() = default;

        void _ready() override;

    protected:
        static void _bind_methods();
    };
}