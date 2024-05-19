#include "./player.hpp"
#include "../utils/constants.hpp"
#include "./control/character.hpp"

namespace ling
{
    Player::Player() : Character()
    {
        // scene::node::set_unique_name(this, name::character::player);
    }

    void Player::_ready()
    {
        Character::_ready();
    }

    void Player::_bind_methods()
    {
    }
}