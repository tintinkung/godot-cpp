if(${CMAKE_ARGV1} MATCHES "-P")
    if(${CMAKE_ARGV3} MATCHES "--program")
        set(GODOT_EDITOR_PROGRAM ${CMAKE_ARGV4} CACHE STRING "")
    else()
        message(FATAL_ERROR "ERROR: No matching argument finding program path")
    endif()
    if(${CMAKE_ARGV5} MATCHES "--project")
        set(GODOT_EDITOR_PROJECT ${CMAKE_ARGV6} CACHE STRING "")
    else()
        message(FATAL_ERROR "ERROR: No matching argument finding project path")
    endif()

    message("Opening godot editor...")
    message("Editor executable: " ${GODOT_EDITOR_PROGRAM})
    message("Project directory: " ${GODOT_EDITOR_PROJECT})

    execute_process(
        COMMAND ${GODOT_EDITOR_PROGRAM} "--path" ${GODOT_EDITOR_PROJECT} "--editor"
    )

    message("Editor closed.")
    unset(GODOT_EDITOR_PROGRAM)
    unset(GODOT_EDITOR_PROJECT)
endif()