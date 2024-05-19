#pragma once
// SPDX-License-Identifier: Unlicense

#include <godot_cpp/classes/object.hpp>

namespace godot
{
    class ClassDB;
};

/// @brief Global gdextension class extends all godot object
class GDExtensionInfo : public godot::Object
{
    GDCLASS(GDExtensionInfo, godot::Object)

public:
    static godot::String name();
    static godot::String version();
    static godot::String godotCPPVersion();

private:
    static void _bind_methods();
};
