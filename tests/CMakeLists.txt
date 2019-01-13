cmake_minimum_required(VERSION  3.5.1)

PROJECT(Tests CXX)

find_package(MPI REQUIRED)
find_package(BLAS REQUIRED)

find_package(MPI)

add_library(petsclib SHARED IMPORTED)
set_property(TARGET petsclib PROPERTY IMPORTED_LOCATION "/usr/lib/petsc/lib/libpetsc_real.so")

include_directories(
        ${MPI_INCLUDE_PATH}

        /usr/lib/slepc/include
        /usr/lib/petsc/include
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
)

link_directories(sparselizard)


LINK_LIBRARIES (${CMAKE_REQUIRED_LIBRARIES})

add_executable(permanent_magnet permanent_magnet.cpp)

target_link_libraries(permanent_magnet
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

add_executable(vector_potential vector_potential.cpp)

target_link_libraries(vector_potential
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(inductionheating inductionheating.cpp)

target_link_libraries(inductionheating
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

add_executable(waveguide3D waveguide3D.cpp)

target_link_libraries(waveguide3D
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

