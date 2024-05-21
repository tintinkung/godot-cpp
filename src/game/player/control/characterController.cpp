
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "../../utils/constants.hpp"
#include "../../utils/input.hpp"
#include "./characterController.hpp"

namespace ling
{
    void CharacterController::_physics_process(double delta_time)
    {
        godot::Engine* engine{ godot::Engine::get_singleton() };

        if (engine->is_editor_hint())
        {
            return;
        }

        godot::Input* input_handler{ input::get() };
        if (input_handler != nullptr)
        {
            this->process_movement_input(input_handler, delta_time);
            this->process_rotation_input(input_handler, delta_time);
            this->process_action_input(input_handler, delta_time);

            m_elapsed_time += delta_time;
            if (m_elapsed_time > 1.0)
            {
                m_elapsed_time = 0.0;
                this->emit_signal(event::position_changed, this->get_parent(), godot::Vector2{
                    this->get_global_position().x, 
                    this->get_global_position().z
                });
            }
        }
    }

    void CharacterController::process_action_input(godot::Input* const input, double delta_time)
    {
        godot::UtilityFunctions::print("process_action_input() not implemented in derived class");
    }

    void CharacterController::process_movement_input(godot::Input* const input, double delta_time)
    {
        godot::UtilityFunctions::print("process_movement_input() not implemented in derived class");
    }

    void CharacterController::process_rotation_input(godot::Input* const input, double delta_time)
    {
        godot::UtilityFunctions::print("process_rotation_input() not implemented in derived class");
    }

    void CharacterController::_bind_methods()
    {
        std::vector<godot::PropertyInfo> move_info{ 
            godot::GetTypeInfo<std::type_identity_t<godot::Vector2>>().get_class_info(), 
            godot::GetTypeInfo<std::type_identity_t<double>>().get_class_info() };

        std::vector<godot::PropertyInfo> rotate_info{ 
            godot::GetTypeInfo<std::type_identity_t<double>>().get_class_info(), 
            godot::GetTypeInfo<std::type_identity_t<double>>().get_class_info() };

        std::vector<godot::PropertyInfo> position_info{ 
            godot::GetTypeInfo<std::type_identity_t<godot::Object*>>().get_class_info(), 
            godot::GetTypeInfo<std::type_identity_t<godot::Vector2>>().get_class_info() };

        godot::ClassDB::add_signal(CharacterController::get_class_static(), 
            godot::MethodInfo(event::character_move, std::forward<decltype(move_info)>(move_info)));

        godot::ClassDB::add_signal(CharacterController::get_class_static(), 
            godot::MethodInfo(event::character_rotate, std::forward<decltype(rotate_info)>(rotate_info)));

        godot::ClassDB::add_signal(CharacterController::get_class_static(), 
            godot::MethodInfo(event::position_changed, std::forward<decltype(position_info)>(position_info)));

        godot::ClassDB::add_signal(CharacterController::get_class_static(), godot::MethodInfo(event::character_jump));

        

        // signal_binding<CharacterController, event::character_move>::add<godot::Vector2, double>();
        // signal_binding<CharacterController, event::character_rotate>::add<double, double>();
        // signal_binding<CharacterController, event::character_shoot>::add<godot::Object*>();
        // signal_binding<CharacterController, event::position_changed>::add<godot::Object*, godot::Vector2>();
    }
}