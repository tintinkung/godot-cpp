#pragma once

#include <concepts>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <memory>

#include "../camera.hpp"
#include "../../utils/constants.hpp"

namespace godot
{
    class ClassDB;
    class Marker2D;
    class Object;
    class Variant;
    struct Vector2;
    class InputEvent;
}

namespace ling
{
    class CharacterController; // forward refs
}

namespace ling
{
    class Character : public godot::CharacterBody3D
    {
        GDCLASS(Character, godot::CharacterBody3D)

    public:
        Character();
        virtual ~Character() = default;

        virtual void _ready() override;
        void _process(double delta_time);
        
    public:
        CharacterController* get_controller() const;
        void set_controller(CharacterController* controller);

    protected:
        double get_movement_speed() const;
        double get_movement_friction() const;
        double get_rotation_speed() const;

        void set_movement_speed(const double move_speed);
        void set_movement_friction(const double move_friction);
        void set_rotation_speed(const double rotation_speed);

        virtual void on_character_jump();
        virtual void on_character_movement(godot::Vector2 movement_velocity, double delta_time);

    protected:
        static void _bind_methods()
        {

            godot::ClassDB::bind_method(godot::D_METHOD("on_character_movement"), &Character::on_character_movement);
            godot::ClassDB::bind_method(godot::D_METHOD("on_character_jump"), &Character::on_character_jump);

            godot::ClassDB::bind_method(godot::D_METHOD("set_movement_speed"), &Character::set_movement_speed);
            godot::ClassDB::bind_method(godot::D_METHOD("get_movement_speed"), &Character::get_movement_speed);
            godot::ClassDB::add_property(Character::get_class_static(),
                godot::PropertyInfo(godot::Variant::Type::FLOAT, godot::String("movement_speed")),
                godot::String("set_movement_speed"), godot::String("get_movement_speed"));

            godot::ClassDB::bind_method(godot::D_METHOD("set_movement_friction"), &Character::set_movement_friction);
            godot::ClassDB::bind_method(godot::D_METHOD("get_movement_friction"), &Character::get_movement_friction);
            godot::ClassDB::add_property(Character::get_class_static(),
                godot::PropertyInfo(godot::Variant::Type::FLOAT, "movement_friction"),
                godot::String("set_movement_friction"), godot::String("get_movement_friction"));

            godot::ClassDB::bind_method(godot::D_METHOD("set_rotation_speed"), &Character::set_rotation_speed);
            godot::ClassDB::bind_method(godot::D_METHOD("get_rotation_speed"), &Character::get_rotation_speed);
            godot::ClassDB::add_property(Character::get_class_static(),
                godot::PropertyInfo(godot::Variant::Type::FLOAT, "rotation_speed"), godot::String("set_rotation_speed"),
                godot::String("get_rotation_speed"));

            std::vector<godot::PropertyInfo> position_info{ 
                godot::GetTypeInfo<std::type_identity_t<godot::Object*>>().get_class_info(), 
                godot::GetTypeInfo<std::type_identity_t<godot::Vector2>>().get_class_info() };

            godot::ClassDB::add_signal(Character::get_class_static(), 
                godot::MethodInfo(event::character_move, std::forward<decltype(position_info)>(position_info)));
        }

    protected:
        // Rate of acceleration/deceleration (unit/s/s)
        double m_movement_friction{ 5.0 };
        // Rate of rotational acceleration/deceleration (unit/s/s)
        double m_rotation_speed{ 10.0 };
        // target movement speed (units/s)
        double m_movement_speed{ 500.0 };
        // target facing angle (radians)
        double m_rotation_angle{ 0.0 };

        double m_jumpHeight{ 3.5f };

        double m_jumpTimeout{ 0.1f };

        double m_fallTimeout{ 0.15f };

        double m_terminalVelocity{ 10.0f };

        double m_jumpTimeoutDelta;
		double m_fallTimeoutDelta;
        double m_verticalVelocity;
        bool m_isOnJump{ false };

        // handles all input related player controls
        CharacterController* m_character_controller{ nullptr };
        
    };
}