cmake_minimum_required(VERSION 3.26)

project(NMRndr VERSION 1.0.0)

# ###################################################################### #
# Setup Options                                                          #
# ###################################################################### #
set(BUILD_EXAMPLES ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Binaries)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ###################################################################### #
# Set C++ Standards                                                      #
# ###################################################################### #
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# ###################################################################### #
# Include CMake Tools                                                    #
# ###################################################################### #
include(CTest)
include(GenerateExportHeader)
include(GoogleTest)
include(Tools/cmake/Git.cmake)
include(Tools/cmake/Builder.cmake)

# ###################################################################### #
# Load Required Packages                                                 #
# ###################################################################### #
find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

# ###################################################################### #
# Load Projects                                                          #
# ###################################################################### #
add_subdirectory(Source/Math)
add_subdirectory(Source/Core)
add_subdirectory(Source/App)
add_subdirectory(Source/SDLApp)

add_subdirectory(Tools)

if(BUILD_EXAMPLES)
    add_subdirectory(Source/Examples)
endif()

if(BUILD_TESTING)
    add_subdirectory(Test)
endif()
