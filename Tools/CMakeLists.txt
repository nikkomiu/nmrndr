include(cmake/ClangTools.cmake)
include(cmake/CppCheck.cmake)

file(GLOB_RECURSE ALL_SOURCE_FILES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/Source/*.h
    ${CMAKE_SOURCE_DIR}/Source/*.c
    ${CMAKE_SOURCE_DIR}/Source/*.hpp
    ${CMAKE_SOURCE_DIR}/Source/*.cpp

    ${CMAKE_SOURCE_DIR}/Tests/*.c
    ${CMAKE_SOURCE_DIR}/Tests/*.h
    ${CMAKE_SOURCE_DIR}/Tests/*.hpp
    ${CMAKE_SOURCE_DIR}/Tests/*.cpp
)

clang_format(SOURCE_FILES ${ALL_SOURCE_FILES})
clang_check(SOURCE_FILES ${ALL_SOURCE_FILES})
clang_tidy(SOURCE_FILES ${ALL_SOURCE_FILES})
