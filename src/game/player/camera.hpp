#pragma once

#include <godot_cpp/classes/camera3d.hpp>

namespace ling
{
    class Camera : public godot::Camera3D
    {
        GDCLASS(Camera, godot::Camera3D)

    public:
        Camera();
        ~Camera() = default;

    protected:
        static void _bind_methods()
        {
        }
    };
}