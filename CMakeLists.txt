cmake_minimum_required(VERSION  3.5.1)

PROJECT(Magnetism CXX)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


enable_testing()


#message (SEND_ERROR ${CMAKE_MODULE_PATH} )


add_compile_options(
        -O3
        -g3
        #-Wall
        )

add_subdirectory(misc)


#add_subdirectory(gmsh_demos/api)


add_subdirectory(mesh_editor)


add_subdirectory(sparselizard_lib)
add_subdirectory(tests)


