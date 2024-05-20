
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

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)
