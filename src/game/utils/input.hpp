#pragma once

namespace godot
{
    class InputMap;
    class Input;
}

namespace ling::inline utils
{
    namespace input
    {
        namespace action
        {
            constexpr inline auto move_left{ "move_left" };
            constexpr inline auto move_right{ "move_right" };
            constexpr inline auto move_up{ "move_up" };
            constexpr inline auto move_down{ "move_down" };
            constexpr inline auto jump{ "jump" };
        }

        struct map
        {
            static godot::InputMap* get();
        };

        godot::Input* get();

        void capture_cursor();
        void hide_cursor();
        void show_cursor();
        bool cursor_visible();
        void load_project_inputs();
        void use_accumulated_inputs(bool enable);
    };
}