cmake_minimum_required(VERSION 3.5.1)
project(scene_editor)

add_compile_options(-std=c++14)

find_package(Eigen3 REQUIRED Core)
find_package(jsoncpp REQUIRED)

cmake_policy(SET CMP0072 OLD)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads)
find_package(Boost REQUIRED COMPONENTS filesystem)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets CONFIG REQUIRED)

add_library(petsclib SHARED IMPORTED)
set_property(TARGET petsclib PROPERTY IMPORTED_LOCATION "/usr/lib/petsc/lib/libpetsc_real.so")

set(JSONCPP_LIBRARIES jsoncpp)

find_package(MPI REQUIRED)
find_package(BLAS REQUIRED)

include_directories(
        include

        /usr/lib/petsc/include
        ${MPI_INCLUDE_PATH}
        /usr/lib/slepc/include

        ../misc/include
        ../sparselizard_lib/sparselizard/src
        ../sparselizard_lib/sparselizard/src/expression
        ../sparselizard_lib/sparselizard/src/expression/operation
        ../sparselizard_lib/sparselizard/src/field
        ../sparselizard_lib/sparselizard/src/formulation
        ../sparselizard_lib/sparselizard/src/gausspoint
        ../sparselizard_lib/sparselizard/src/geometry
        ../sparselizard_lib/sparselizard/src/mesh
        ../sparselizard_lib/sparselizard/src/mesh/gmsh
        ../sparselizard_lib/sparselizard/src/resolution
        ../sparselizard_lib/sparselizard/src/shapefunction
        ../sparselizard_lib/sparselizard/src/shapefunction/hierarchical
        ../sparselizard_lib/sparselizard/src/shapefunction/hierarchical/h1
        ../sparselizard_lib/sparselizard/src/shapefunction/hierarchical/hcurl
        ../sparselizard_lib/sparselizard/src/shapefunction/hierarchical/meca
        ../sparselizard_lib/sparselizard/src/shapefunction/lagrange

        ${EIGEN3_INCLUDE_DIRS}
        /usr/include/jsoncpp
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
)

link_directories(
        ${Boost_LIBRARY_DIR}
        misc
        pthread
        solid3


)

add_executable(mesh_editor
        src/main.cpp
        src/glwidget.cpp
        include/glwidget.h
        src/mainwindow.cpp
        include/mainwindow.h
        src/mesh_holder.cpp
        include/mesh_holder.h
        src/window.cpp
        include/window.h
        )


target_link_libraries(mesh_editor
        Qt5::Widgets
        pthread
        Sparselizard
        misc
        ${CMAKE_THREAD_LIBS_INIT}
        ${JSONCPP_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        -lboost_filesystem
        -lboost_system
        #-fsanitize=address
        -lblas
        -lslepc
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        )

