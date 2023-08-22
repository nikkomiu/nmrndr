set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Binaries/Examples)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(NM_PKG_PREFIX "EXAMPLE_NM")

add_subdirectory(0_Trajectory)
add_subdirectory(1_RotMatClock)
add_subdirectory(2_ShadowSphere)
add_subdirectory(3_RenderSphere)
add_subdirectory(4_FirstScene)
