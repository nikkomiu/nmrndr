set(PKG_NAME "NMRndrApp")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp
)
add_executable(${PKG_NAME} ${SOURCES})

target_link_libraries(${PKG_NAME}
    PUBLIC
        NMRndrCore
)

target_include_directories(${PKG_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
)

target_compile_options(${PKG_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Werror -pedantic-errors -Wextra -Wconversion -Wsign-conversion
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX
    >
)
