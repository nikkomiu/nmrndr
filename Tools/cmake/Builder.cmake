# set(NM_USE_EXE_PREFIX ON)
# set(NM_PKG_PREFIX "NM_")

function(nm_build)
    set(options "")
    set(oneValueArgs PKG_PREFIX PKG_NAME PKG_TYPE IDE_FOLDER)
    set(multiValueArgs PUBLIC_LINK_LIBRARIES PRIVATE_LINK_LIBRARIES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # set default PKG_PREFIX if not specified
    if(NOT ARG_PKG_PREFIX)
        if(NOT NM_PKG_PREFIX)
            set(ARG_PKG_PREFIX "NM")
        else()
            set(ARG_PKG_PREFIX ${NM_PKG_PREFIX})
        endif()
    endif()

    # set default IDE folder if not specified
    if(NOT ARG_IDE_FOLDER AND ${ARG_PKG_TYPE} STREQUAL "EXE")
        set(ARG_IDE_FOLDER "Renderer")
    elseif(NOT ARG_IDE_FOLDER)
        set(ARG_IDE_FOLDER "Libraries")
    endif()

    set(PKG_NAME "${ARG_PKG_PREFIX}${ARG_PKG_NAME}")
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.c

        ${CMAKE_CURRENT_SOURCE_DIR}/Public/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp
    )

    if(${ARG_PKG_TYPE} STREQUAL "EXE")
        add_executable(${PKG_NAME} ${SOURCES})

        if(NOT _USE_EXE_PREFIX)
            set_target_properties(${PKG_NAME} PROPERTIES
                OUTPUT_NAME ${ARG_PKG_NAME}
            )
        else()
            set_target_properties(${PKG_NAME} PROPERTIES
                OUTPUT_NAME ${PKG_NAME}
            )
        endif()
    else()
        add_library(${PKG_NAME} ${ARG_PKG_TYPE} ${SOURCES})
    endif()

    target_link_libraries(${PKG_NAME}
        PUBLIC
            ${ARG_PUBLIC_LINK_LIBRARIES}
        PRIVATE
            ${ARG_PRIVATE_LINK_LIBRARIES}
    )

    set_target_properties(${PKG_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        FOLDER ${ARG_IDE_FOLDER}
    )

    target_include_directories(${PKG_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Public>
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

    # Add code coverage flags if building in test mode and not an executable
    if(NOT ${ARG_PKG_TYPE} STREQUAL "EXE" AND "${WITH_COVERAGE}" STREQUAL "ON")
        message(STATUS "Building ${PKG_NAME} with code coverage")

        # TODO: Add support for code coverage on Windows
        target_compile_options(${PKG_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_libraries(${PKG_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    endif()
endfunction()

function(nm_test)
    set(options "")
    set(oneValueArgs PKG_PREFIX PKG_NAME PKG_TYPE)
    set(multiValueArgs LINK_LIBRARIES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # set default PKG_PREFIX if not specified
    if(NOT ARG_PKG_PREFIX)
        set(ARG_PKG_PREFIX "NM")
    endif()

    set(PKG_NAME "Test${ARG_PKG_TYPE}${ARG_PKG_PREFIX}${ARG_PKG_NAME}")
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Public/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp
    )

    add_executable(${PKG_NAME} ${SOURCES})
    set_target_properties(${PKG_NAME} PROPERTIES
        FOLDER "Test"
    )

    target_link_libraries(${PKG_NAME}
        PUBLIC
            GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main

            ${ARG_LINK_LIBRARIES}
    )

    # TODO: enable warnings for tests
    # target_compile_options(${PKG_NAME} PRIVATE
    #     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    #         -Wall -Werror -pedantic-errors -Wextra -Wconversion -Wsign-conversion
    #     >
    #     $<$<CXX_COMPILER_ID:MSVC>:
    #         /W4 /WX
    #     >
    # )

    # TODO: Add support for code coverage on Windows
    target_compile_options(${PKG_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_libraries(${PKG_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)

    target_include_directories(${PKG_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
    )

    gtest_discover_tests(${PKG_NAME}
        TEST_PREFIX "${ARG_PKG_TYPE}/${ARG_PKG_NAME}/"
    )

    if("${WITH_COVERAGE}" STREQUAL "ON")
        # set_target_properties(${PKG_NAME} PROPERTIES
        #     EXCLUDE_FROM_ALL TRUE
        # )

        add_custom_target(${PKG_NAME}Coverage # ALL
            COMMAND $<TARGET_FILE:${PKG_NAME}> --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/default.xml
            DEPENDS ${PKG_NAME}
        )

        # Generate coverage data from raw profile data
        add_custom_command(
            TARGET ${PKG_NAME}Coverage
            COMMAND llvm-profdata merge -o ${PKG_NAME}.profdata default.profraw
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}.profdata
        )

        # Generate Summary coverage report (for GitLab CI coverage percentage)
        add_custom_command(
            TARGET ${PKG_NAME}Coverage
            COMMAND llvm-cov show -o ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME} ${PKG_NAME} -instr-profile=${PKG_NAME}.profdata
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        )

        # Generate LCOV coverage report
        add_custom_command(
            TARGET ${PKG_NAME}Coverage
            COMMAND llvm-cov export -format=lcov ${PKG_NAME} -instr-profile=${PKG_NAME}.profdata > ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME}/lcov.info
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            BYPRODUCTS ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME}/lcov.info
        )

        # Generate HTML coverage report
        add_custom_command(
            TARGET ${PKG_NAME}Coverage
            COMMAND llvm-cov show -format html -o ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME} ${PKG_NAME} -instr-profile=${PKG_NAME}.profdata
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            BYPRODUCTS ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME}/index.html
        )

        # Generate Cobertura coverage report from lcov (for GitLab CI coverage reporting)
        add_custom_target(${PKG_NAME}Cobertura
            DEPENDS ${PKG_NAME}Coverage
            COMMAND lcov_cobertura ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME}/lcov.info --base-dir ${CMAKE_SOURCE_DIR} --output ${CMAKE_BINARY_DIR}/coverage/${PKG_NAME}/cobertura.xml
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()
endfunction()
