set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Binaries/Examples)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(NM_PKG_PREFIX "EXAMPLE_NM")

add_subdirectory(RotMatClock)
add_subdirectory(Trajectory)
add_subdirectory(ShadowSphere)
