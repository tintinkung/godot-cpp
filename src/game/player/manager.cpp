#include <godot_cpp/classes/collision_polygon2d.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "./control/character.hpp"
#include "./playerController.hpp"
#include "./manager.hpp"
#include "../utils/input.hpp"

namespace ling
{
    Manager::Manager()
    {
        // scene::node::set_unique_name(this, name::level::level1);
        this->m_controller = memnew(PlayerController);
        this->activate(true);
        this->m_player->set_controller(this->m_controller);
    }

    void Manager::_ready()
    {
        godot::Node* box{ this->find_child("physicsBox") };
        m_physics_box = godot::Object::cast_to<godot::RigidBody2D>(box);

        this->add_child(m_player);

        if (m_player->get_controller() != nullptr)
        {

            m_player->get_controller()->connect(event::position_changed, godot::Callable(this, "on_character_position_changed"));
        }
    }

    void Manager::_process(double delta_time)
    {
        godot::Engine* engine{ godot::Engine::get_singleton() };

        if (engine->is_editor_hint()) return;

        if (this->active() && input::cursor_visible()) [[unlikely]]
            input::hide_cursor();
        else if (!this->active() && !input::cursor_visible()) [[unlikely]]
            input::show_cursor();

        this->queue_redraw();
    }

    void Manager::_draw()
    {
        if (this->active()) [[likely]]
        {
            godot::Point2 mouse_pos{ this->get_global_mouse_position() };
            this->draw_circle(mouse_pos, 5, { "DARK_CYAN" });
        }
    }

    void Manager::activate(bool active)
    {
        m_active = active;
    }

    bool Manager::active() const
    {
        return m_active;
    }

    void Manager::on_physics_box_entered(godot::Node* node) const
    {
        // console::get()->print("{} > {}", io::yellow("projectile"), to<std::string>(node->get_name()));
        godot::UtilityFunctions::print("physic box entered:", node->get_name());
    }

    void Manager::on_physics_box_exited(godot::Node* node) const
    {
        // console::get()->print("{} < {}", io::red("projectile"), to<std::string>(node->get_name()));
        godot::UtilityFunctions::print("physic box exited:", node->get_name());
    }

    void Manager::on_character_position_changed(const godot::Object* const node,
                                              godot::Vector2 location) const
    {
        godot::UtilityFunctions::print("location: x:", location.x, " y: ", location.y);
        // auto console{ console::get() };
        // console->print("{} ({},{})", io::green(to<std::string>(node->get_class()) + " location: "),
        //                io::orange(location.x), io::orange(location.y));
    }

    void Manager::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("on_character_position_changed"), &Manager::on_character_position_changed);
        godot::ClassDB::bind_method(godot::D_METHOD("on_physics_box_entered"), &Manager::on_physics_box_entered);
        godot::ClassDB::bind_method(godot::D_METHOD("on_physics_box_exited"), &Manager::on_physics_box_exited);

        // bind_member_function(Level, on_character_position_changed);
        // bind_member_function(Level, on_player_spawn_projectile);
        // bind_member_function(Level, on_physics_box_entered);
        // bind_member_function(Level, on_physics_box_exited);
    }
}