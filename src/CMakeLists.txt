
# Include all source files in this directory
# file(GLOB_RECURSE SRC_FILES
#     CONFIGURE_DEPENDS
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/game/utils/*.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/game/utils/*.cpp"
# )

file(GLOB_RECURSE PLAYER_FILES 
    ${PROJECT_SOURCE_DIR}/src/game/utils/*.[hc]pp 
    ${PROJECT_SOURCE_DIR}/src/game/utils/*.[hc]
)

file(GLOB_RECURSE UTIL_FILES 
    ${PROJECT_SOURCE_DIR}/src/game/player/*.[hc]pp
    ${PROJECT_SOURCE_DIR}/src/game/player/*.[hc]
)



# Set the target
target_sources(${PROJECT_NAME}
    PRIVATE 
        ${PLAYER_FILES}
        ${UTIL_FILES}
        GDExtensionInfo.cpp
        GDExtensionInfo.hpp
        RegisterExtension.cpp
)

# target_sources(${PROJECT_NAME}
#     PRIVATE 
#         GDExtensionInfo.cpp
#         GDExtensionInfo.hpp
#         RegisterExtension.cpp
#         game/player/camera.cpp
#         game/player/camera.hpp
#         game/player/control/character.cpp
#         game/player/control/character.hpp
#         game/player/control/characterController.cpp
#         game/utils/constants.hpp
#         game/utils/input.hpp
#         game/utils/input.cpp
# )

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)
