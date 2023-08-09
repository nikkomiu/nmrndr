set(PKG_NAME "NMRndrCoreUnitTests")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp
)

add_executable(${PKG_NAME} ${SOURCES})
set_target_properties(${PKG_NAME} PROPERTIES
    FOLDER "Tests"
)

target_link_libraries(${PKG_NAME}
    PUBLIC
        GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main

        NMRndrCore
)

target_include_directories(${PKG_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
)

gtest_discover_tests(${PKG_NAME}
    TEST_PREFIX "Unit/Core/"
)
