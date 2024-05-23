#include <godot_cpp/variant/utility_functions.hpp>

#include "./player.hpp"
#include "../utils/constants.hpp"
#include "../utils/input.hpp"
#include "./control/character.hpp"

namespace ling
{
    Player::Player() : Character()
    {
        // Assign controller
        this->m_controller = memnew(PlayerController);
        this->set_controller(this->m_controller);
        
    }

    void Player::_ready()
    {
        // utils::input::capture_cursor();
        Character::_ready();
        
        Node3D* head{ godot::Object::cast_to<Node3D>(this->find_child("Head")) };

        if(head != nullptr) 
        {
            this->m_head = head;
            head->add_child(m_camera);
        }

        this->m_controller->connect(event::position_changed, godot::Callable(this, "on_character_position_changed"));
    }

    void Player::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event)
    {
        if(godot::InputEventMouseMotion *mouse_event = godot::Object::cast_to<godot::InputEventMouseMotion>(*p_event))
        {
            if (this->m_head != nullptr)
            {
                this->m_head->rotate_y(-mouse_event->get_relative().x * 0.005f);
                this->m_camera->rotate_x(-mouse_event->get_relative().y * 0.005f);

                real_t clamp_rotation_x = godot::Math::clamp(
                    this->m_camera->get_rotation().x, 
                    godot::Math::deg_to_rad(-60.0f), 
                    godot::Math::deg_to_rad(75.0f)
                );

                this->m_camera->set_rotation({ clamp_rotation_x, m_camera->get_rotation().y, m_camera->get_rotation().z });

            }
        }
    }

    void Player::on_character_movement(godot::Vector2 movement_velocity, double delta_time)
    {
        double increment = this->m_movement_friction * delta_time;
        godot::Basis basis = this->m_head->get_transform().basis;
        godot::Vector3 direction = basis.xform(godot::Vector3({ movement_velocity.x, 0, movement_velocity.y })).normalized();

        godot::Vector3 velocity{ this->get_velocity().lerp(direction, increment) };

        this->translate(velocity * this->get_movement_speed() * delta_time);

        godot::Vector3 verticalVelocity = godot::Vector3(0.0f, this->m_verticalVelocity, 0.0f); 


        this->set_velocity(direction - verticalVelocity);
        this->move_and_slide();
    }

    
    
    void Player::on_character_position_changed(const godot::Object* const node, godot::Vector2 location) const
    {
        godot::UtilityFunctions::print("location: x:", location.x, " y: ", location.y);
    }

    void Player::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("on_character_position_changed"), &Player::on_character_position_changed);
    }
}