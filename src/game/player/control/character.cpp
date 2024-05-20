#include <array>
#include <tuple>
#include <type_traits>
#include <vector>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>


#include "./character.hpp"

namespace ling
{
    Character::Character()
    {
        this->set_motion_mode(MotionMode::MOTION_MODE_FLOATING);
    }

    void Character::_ready()
    {
        Node2D* controller{ godot::Object::cast_to<Node2D>((Object*) m_character_controller) };
        this->add_child(m_camera);
        this->add_child(controller);

        // m_firing_point = gdcast<godot::Marker2D>(
        //     this->find_child(name::character::firing_pt, true, false));

        // runtime_assert(m_firing_point != nullptr);
        // if (!engine::editor_active())
        //     runtime_assert(m_character_controller != nullptr);

        if (m_character_controller != nullptr)
        {
            // godot::Callable&& callback_movement{ 
            //     std::forward<godot::Callable>(
            //     std::get<0>(
            //     std::forward_as_tuple(godot::Callable(this, "on_character_movement"), 
            // this))) };

            controller->connect(event::character_move, godot::Callable(this, "on_character_movement"));

            // godot::Callable&& callback_rotate{ 
            //     std::forward<godot::Callable>(
            //     std::get<0>(
            //     std::forward_as_tuple(godot::Callable(this, "on_character_rotate"), 
            // this))) };

            controller->connect(event::character_rotate, godot::Callable(this, "on_character_rotate"));
                
        //     signal<event::character_move>::connect<CharacterController>(m_character_controller)
        //     <=>
        //         signal_callback(this, on_character_movement);

        //     signal<event::character_rotate>::connect<CharacterController>(m_character_controller)
        //     <=>
        //         signal_callback(this, on_character_rotate);
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
        godot::Vector2 velocity{ this->get_velocity().lerp(movement_velocity, increment) };
        velocity = velocity.clamp({ -1.0, -1.0 }, { 1.0, 1.0 });
        this->translate(velocity * this->get_movement_speed() * delta_time);
        this->set_velocity(velocity);
        this->move_and_slide();
    }

    void Character::on_character_rotate(double rotation_angle, double delta_time)
    {
        double smoothed_angle
            = godot::Math::lerp_angle(this->get_rotation(), rotation_angle, m_rotation_speed * delta_time);
        this->set_rotation(smoothed_angle);
    }

    void Character::on_character_shoot()
    {
        // TODO: fix this
        this->emit_signal(event::spawn_projectile, m_firing_point);
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