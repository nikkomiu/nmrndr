set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Binaries/Tools)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(AssMan)
add_subdirectory(PaxBuild)
