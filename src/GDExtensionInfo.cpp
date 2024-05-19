// SPDX-License-Identifier: Unlicense

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/version.hpp>

#include "GDExtensionInfo.hpp"
#include "Version.h"

/// @file
/// GDExtensionTemplate example implementation.

/*!
@brief Get the version string for this extension.

@details
The version string is generated by cmake using src/Version.h.in.

It uses the form "<project name> <last tag>-<# commits since last tag>-<short commit hash>".
If there are no commits since the last tag, only the tag is shown.

@return The version string (e.g. "Foo v1.2.3-gdedbd01").
*/
godot::String GDExtensionInfo::version()
{
    return VersionInfo::VERSION_STR.data();
}

/*!
@brief Get the name of the GDExtension enabled
@return "Ling Game"
*/
godot::String GDExtensionInfo::name()
{
    return "Ling Game";
}

/*!
@brief Get the godot-cpp version string for this extension.

@details
The version string is generated using godot-cpp's core/version.hpp.

@return The version string (e.g. "godot-cpp v4.2.0-stable").
*/
godot::String GDExtensionInfo::godotCPPVersion()
{
    return "godot-cpp v" + godot::uitos(GODOT_VERSION_MAJOR) //
           + "." + godot::uitos(GODOT_VERSION_MINOR)         //
           + "." + godot::uitos(GODOT_VERSION_PATCH)         //
           + "-" + GODOT_VERSION_STATUS;                     //
}

/// Bind our methods so GDScript can access them.
void GDExtensionInfo::_bind_methods()
{
    godot::ClassDB::bind_static_method("GDExtensionInfo", godot::D_METHOD("name"), &GDExtensionInfo::name);
    godot::ClassDB::bind_static_method("GDExtensionInfo", godot::D_METHOD("version"), &GDExtensionInfo::version);
    godot::ClassDB::bind_static_method(
        "GDExtensionInfo", godot::D_METHOD("godot_cpp_version"), &GDExtensionInfo::godotCPPVersion);
}
