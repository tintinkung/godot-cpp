#pragma once
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

#include "./control/character.hpp"
#include "./playerController.hpp"


namespace ling
{
    class Player : public Character
    {
        GDCLASS(Player, Character)

    public:
        Player();
        ~Player() = default;
        void _ready() override;
        void _unhandled_input(const godot::Ref<godot::InputEvent> &p_event);
    protected:
        static void _bind_methods();
        void on_character_position_changed(const godot::Object* const obj, godot::Vector2 location) const;
        void on_character_movement(godot::Vector2 movement_velocity, double delta_time);
    private:
        PlayerController* m_controller{ nullptr };
        // marker identifying location where to spwwn projectiles
        godot::Node3D* m_head{ nullptr };
        // the player character camera
        Camera* m_camera{ memnew(Camera) };
    };
}