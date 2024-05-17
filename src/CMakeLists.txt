# SPDX-License-Identifier: Unlicense

target_sources(${PROJECT_NAME}
    PRIVATE
        GDExtensionInfo.hpp # Global object info
        GDExtensionInfo.cpp
        RegisterExtension.cpp # Godot Extension Register
)

target_include_directories(${PROJECT_NAME} PRIVATE "src" )
