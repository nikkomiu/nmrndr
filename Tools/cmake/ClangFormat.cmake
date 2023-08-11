file(GLOB_RECURSE ALL_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/Source/*.h
    ${CMAKE_SOURCE_DIR}/Source/*.c
    ${CMAKE_SOURCE_DIR}/Source/*.hpp
    ${CMAKE_SOURCE_DIR}/Source/*.cpp

    ${CMAKE_SOURCE_DIR}/Tests/*.c
    ${CMAKE_SOURCE_DIR}/Tests/*.h
    ${CMAKE_SOURCE_DIR}/Tests/*.hpp
    ${CMAKE_SOURCE_DIR}/Tests/*.cpp
)

add_custom_target(
    ClangFormatDryRun
    COMMAND /usr/bin/clang-format
    --Werror
    -n
    ${ALL_SOURCE_FILES}
)

add_custom_target(
    ClangFormat
    COMMAND /usr/bin/clang-format
    --Werror
    -i
    ${ALL_SOURCE_FILES}
)

add_custom_target(
    ClangCheck
    COMMAND /usr/bin/clang-check
    -analyze
    -p .
    --fixit
    ${ALL_SOURCE_FILES}
)

add_custom_target(
    ClangCheckDryRun
    COMMAND /usr/bin/clang-check
    -analyze
    -p .
    ${ALL_SOURCE_FILES}
)

# add_custom_target(
#     ClangTidyDryRun
#     COMMAND /usr/bin/clang-tidy
#     -p .
#     -checks=*
#     -header-filter=""
#     -warnings-as-errors=*
#     -quiet
#     ${ALL_SOURCE_FILES}
# )

# add_custom_target(
#     ClangTidy
#     COMMAND /usr/bin/clang-tidy
#     -p .
#     -checks=*
#     -header-filter=""
#     -warnings-as-errors=*
#     -quiet
#     -fix
#     ${ALL_SOURCE_FILES}
# )
