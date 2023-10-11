macro(clang_format)
    set(options "")
    set(oneValueArgs "")
    set(multiValueArgs SOURCE_FILES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_custom_target(
        ClangFormatDryRun
        COMMAND /usr/bin/clang-format
        --Werror
        -n
        ${ARG_SOURCE_FILES}
    )

    add_custom_target(
        ClangFormat
        COMMAND /usr/bin/clang-format
        --Werror
        -i
        ${ARG_SOURCE_FILES}
    )
endmacro()

macro(clang_check)
    set(options "")
    set(oneValueArgs "")
    set(multiValueArgs SOURCE_FILES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_custom_target(
        ClangCheck
        COMMAND /usr/bin/clang-check
        -analyze
        -p .
        --fixit
        ${ARG_SOURCE_FILES}
    )

    add_custom_target(
        ClangCheckDryRun
        COMMAND /usr/bin/clang-check
        -analyze
        -p .
        ${ARG_SOURCE_FILES}
    )
endmacro()

macro(clang_tidy)
    set(options "")
    set(oneValueArgs "")
    set(multiValueArgs SOURCE_FILES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # cmake -G Ninja -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    # clang-tidy-11 -format-style=file -header-filter=. -p build

    message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

    add_custom_target(
        ClangTidyDryRun
        COMMAND /usr/bin/clang-tidy
        -p ${CMAKE_BINARY_DIR}
        -checks=*
        -header-filter=""
        -warnings-as-errors=*
        -quiet
        ${ARG_SOURCE_FILES}
    )

    add_custom_target(
        ClangTidy
        COMMAND /usr/bin/clang-tidy
        -p ${CMAKE_BINARY_DIR}
        -checks=*
        -header-filter=""
        -warnings-as-errors=*
        -quiet
        -fix
        ${ARG_SOURCE_FILES}
    )
endmacro()
