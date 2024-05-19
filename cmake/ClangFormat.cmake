# SPDX-License-Identifier: Unlicense

find_program( CLANG_FORMAT_PROGRAM NAMES clang-format )



if ( CLANG_FORMAT_PROGRAM )
    # get version information
    execute_process(
        COMMAND "${CLANG_FORMAT_PROGRAM}" --version
        OUTPUT_VARIABLE CLANG_FORMAT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Recursively find cpp and hpp files in src
    file(GLOB_RECURSE
        ALL_CXX_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]pp"
    )

    message( STATUS "Using clang-format: ${CLANG_FORMAT_PROGRAM} (${CLANG_FORMAT_VERSION})" )

    # Remove some files from the list
    list( FILTER ALL_CXX_SOURCE_FILES EXCLUDE REGEX ".*/extern/.*" )
    list( FILTER ALL_CXX_SOURCE_FILES EXCLUDE REGEX ".*/gen/.*" )
    list( FILTER ALL_CXX_SOURCE_FILES EXCLUDE REGEX ".*/*.gdextension.in" )
    list( FILTER ALL_CXX_SOURCE_FILES EXCLUDE REGEX ".*/Version.h.in" )

    add_custom_target( clang-format
        COMMAND "${CLANG_FORMAT_PROGRAM}" -i -style=file --verbose ${ALL_CXX_SOURCE_FILES}
        COMMENT "Running clang-format..."
        COMMAND_EXPAND_LISTS
        VERBATIM
    )

    unset( CLANG_FORMAT_VERSION )
    unset( ALL_CXX_SOURCE_FILES )
endif()
