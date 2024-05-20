#include <vector>

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "../utils/constants.hpp"
#include "./player.hpp"
#include "./playerController.hpp"

namespace godot
{
    class RigidBody2D;
}

namespace ling
{
    class Player;

    class Manager : public godot::Node2D
    {
        GDCLASS(Manager, godot::Node2D)

    public:
        Manager();
        ~Manager() = default;

        virtual void _ready() override;
        void _draw() override;
        void _process(double delta_time) override;

        void activate(bool active = true);
        bool active() const;

    protected:
        static void _bind_methods();

        void on_physics_box_entered(godot::Node* node) const;
        void on_physics_box_exited(godot::Node* node) const;
        void on_character_position_changed(const godot::Object* const obj, godot::Vector2 location) const;

    private:
        std::atomic<bool> m_active{ false };
        godot::Node* m_background{ nullptr };
        PlayerController* m_controller{ nullptr };
        Player* m_player{ memnew(Player) };
        godot::RigidBody2D* m_physics_box{ nullptr };
    };
}