// Copied from godot-cpp/test/src and modified.

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "GDExtensionInfo.hpp"
#include "game/player/camera.hpp"
#include "game/player/control/character.hpp"
#include "game/player/control/characterController.hpp"
#include "game/player/player.hpp"
#include "game/player/manager.hpp"
#include "game/player/playerController.hpp"

/// @file
/// Register our classes with Godot.

namespace
{
    /// @brief Called by Godot to let us register our classes with Godot.
    ///
    /// @param p_level the level being initialized by Godot
    ///
    /// @see GDExtensionInit
    void initializeExtension(godot::ModuleInitializationLevel p_level)
    {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        {
            return;
        }

        godot::ClassDB::register_class<GDExtensionInfo>();

        // godot::ClassDB::register_class<ling::Projectile>();
        // godot::ClassDB::register_class<ling::ProjectileSpawner>();

        godot::ClassDB::register_abstract_class<ling::CharacterController>();
        godot::ClassDB::register_class<ling::PlayerController>(true);
        // godot::ClassDB::register_class<ling::EnemyController>();

        godot::ClassDB::register_class<ling::Camera>();
        godot::ClassDB::register_class<ling::Character>();
        // godot::ClassDB::register_class<ling::Enemy>();
        godot::ClassDB::register_class<ling::Player>();

        godot::ClassDB::register_class<ling::Manager>();
        // godot::ClassDB::register_class<ling::MainDialog>();
        // godot::ClassDB::register_class<ling::Main>();

        // godot::ClassDB::register_class<console>();
    }

    /// @brief Called by Godot to let us do any cleanup.
    ///
    /// @see GDExtensionInit
    void uninitializeExtension(godot::ModuleInitializationLevel p_level)
    {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        {
            return;
        }
    }
}

extern "C"
{
    /// @brief This is the entry point for the shared library.
    ///
    /// @note The name of this function must match the "entry_symbol" in
    /// templates/template.*.gdextension.in
    ///
    /// @param p_get_proc_address the interface (need more info)
    /// @param p_library the library (need more info)
    /// @param r_initialization the intialization (need more info)
    ///
    /// @returns GDExtensionBool
    GDExtensionBool GDE_EXPORT GDExtensionInit(GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization)
    {
        {
            godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

            init_obj.register_initializer(initializeExtension);
            init_obj.register_terminator(uninitializeExtension);
            init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

            return init_obj.init();
        }
    }
}
