#include <array>
#include <tuple>
#include <type_traits>
#include <vector>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "./character.hpp"

namespace ling
{
    Character::Character()
    {
        this->set_motion_mode(MotionMode::MOTION_MODE_GROUNDED);
    }

    void Character::_ready()
    {
        Node3D* controller{ godot::Object::cast_to<Node3D>((Object*) m_character_controller) };
        
        if (m_character_controller != nullptr)
        {
            this->add_child(controller);
            controller->connect(event::character_move, godot::Callable(this, "on_character_movement"));
            controller->connect(event::character_jump, godot::Callable(this, "on_character_jump"));

            m_jumpTimeoutDelta = m_jumpTimeout;
		    m_fallTimeoutDelta = m_fallTimeout;
        }
    }

    void Character::set_controller(CharacterController* controller)
    {
        m_character_controller = controller;
        // runtime_assert(m_character_controller != nullptr);
    }

    CharacterController* Character::get_controller() const
    {
        return m_character_controller;
    }

    void Character::on_character_movement(godot::Vector2 movement_velocity, double delta_time)
    {
        double increment = m_movement_friction * delta_time;
        godot::Basis basis = this->get_transform().get_basis();
        godot::Vector3 direction = basis.xform_inv({ movement_velocity.x, 0, movement_velocity.y });

        godot::Vector3 velocity{ this->get_velocity().lerp(direction, increment) };

        this->translate(velocity * this->get_movement_speed() * delta_time);
        this->set_velocity({ direction.normalized().x, (real_t) delta_time * (real_t) -98.0f, direction.normalized().z });
        this->move_and_slide();
    }

    void Character::on_character_jump()
    {
        if(this->is_on_floor())
        {
            m_verticalVelocity = -m_jumpHeight;
            godot::UtilityFunctions::print("Updated Velocity: ", m_verticalVelocity, " delta: ", m_jumpTimeoutDelta);
            this->set_motion_mode(MotionMode::MOTION_MODE_GROUNDED);
            m_isOnJump = true;
        }
    }

    void Character::_process(double delta_time)
    {
        // apply gravity over time if under terminal (multiply by delta time twice to linearly speed up over time)
        if(!this->is_on_floor())
        {
            if (m_verticalVelocity < m_terminalVelocity)
            {
                m_verticalVelocity += 9.8f * delta_time;
            }
        }
        else
        {
            if(!m_isOnJump) 
            {
                m_verticalVelocity = 2.0f;
                this->set_motion_mode(MotionMode::MOTION_MODE_GROUNDED);
            }
            else m_isOnJump = false;
        }
    }

    double Character::get_movement_speed() const
    {
        return m_movement_speed;
    }

    void Character::set_movement_speed(const double move_speed)
    {
        m_movement_speed = move_speed;
    }

    double Character::get_movement_friction() const
    {
        return m_movement_friction;
    }

    void Character::set_movement_friction(const double move_friction)
    {
        m_movement_friction = move_friction;
    }

    double Character::get_rotation_speed() const
    {
        return m_rotation_speed;
    }

    void Character::set_rotation_speed(const double rotation_speed)
    {
        m_rotation_speed = rotation_speed;
    }
}