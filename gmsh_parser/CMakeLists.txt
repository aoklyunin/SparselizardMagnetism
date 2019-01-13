cmake_minimum_required(VERSION  3.5.1)


PROJECT(gmsh_parser CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}")

include_directories(
    ../misc/include
)


add_library(
        ${PROJECT_NAME}
        gmsh_parser.cpp
        gmsh_parser.h
)


add_executable(test_gmsh_reader test_gmsh_reader.cpp gmsh_parser.cpp gmsh_parser.h)

target_link_libraries(test_gmsh_reader
        misc
        )

