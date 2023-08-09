cmake_minimum_required(VERSION 3.20)

project(NMRndr VERSION 1.0.0)

# ###################################################################### #
# Setup Options                                                          #
# ###################################################################### #
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
include(Tools/cmake/ClangFormat.cmake)
include(Tools/cmake/CppCheck.cmake)
include(Tools/cmake/Git.cmake)

# ###################################################################### #
# Load Required Packages                                                 #
# ###################################################################### #
find_package(GTest CONFIG REQUIRED)

# ###################################################################### #
# Load Projects                                                          #
# ###################################################################### #
add_subdirectory(Source/Core)
add_subdirectory(Source/App)

if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()
