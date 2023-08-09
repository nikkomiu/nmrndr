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
    ClangFormat
    ALL
    COMMAND /usr/bin/clang-format
    --Werror
    -i
    ${ALL_SOURCE_FILES}
)
