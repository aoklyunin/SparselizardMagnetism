cmake_minimum_required(VERSION  3.5.1)


PROJECT(Sparselizard CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}")

enable_language (Fortran CXX C)
find_package(MPI)
set(CMAKE_Fortran_COMPILE_FLAGS "${CMAKE_Fortran_COMPILE_FLAGS} ${MPI_Fortran_COMPILE_FLAGS}")
set(CMAKE_Fortran_LINK_FLAGS "${CMAKE_Fortran_LINK_FLAGS} ${MPI_Fortran_LINK_FLAGS}")
include_directories(SYSTEM ${MPI_Fortran_INCLUDE_PATH})

add_library(petsclib SHARED IMPORTED)
set_property(TARGET petsclib PROPERTY IMPORTED_LOCATION "/usr/lib/petsc/lib/libpetsc_real.so")

find_package(BLAS REQUIRED)

include_directories(
        ${MPI_INCLUDE_PATH}


        /usr/lib/slepc/include
        /usr/lib/petsc/include

        sparselizard/src
        sparselizard/src/mesh
        sparselizard/src/mesh/gmsh

        sparselizard/src/shapefunction
        sparselizard/src/shapefunction/hierarchical
        sparselizard/src/shapefunction/hierarchical/h1
        sparselizard/src/shapefunction/hierarchical/hcurl
        sparselizard/src/shapefunction/hierarchical/meca
        sparselizard/src/shapefunction/lagrange

        sparselizard/src/expression
        sparselizard/src/expression/operation
        sparselizard/src/field
        sparselizard/src/formulation
        sparselizard/src/gausspoint
        sparselizard/src/geometry

        sparselizard/src/resolution

)


add_library(
        ${PROJECT_NAME}
        sparselizard/src/densematrix.cpp
        sparselizard/src/element.cpp
        sparselizard/src/harmonic.cpp
        sparselizard/src/intdensematrix.cpp
        sparselizard/src/myfft.cpp
        sparselizard/src/universe.cpp
        sparselizard/src/wallclock.cpp



        sparselizard/src/expression/expression.cpp
        sparselizard/src/expression/integration.cpp
        sparselizard/src/expression/parameter.cpp
        sparselizard/src/expression/parameterselectedregion.cpp
        sparselizard/src/expression/operation/mathop.cpp
        sparselizard/src/expression/operation/opabs.cpp
        sparselizard/src/expression/operation/opacos.cpp
        sparselizard/src/expression/operation/opasin.cpp
        sparselizard/src/expression/operation/opatan.cpp
        sparselizard/src/expression/operation/opcondition.cpp
        sparselizard/src/expression/operation/opconstant.cpp
        sparselizard/src/expression/operation/opcos.cpp
        sparselizard/src/expression/operation/opdetjac.cpp
        sparselizard/src/expression/operation/opdof.cpp
        sparselizard/src/expression/operation/operation.cpp
        sparselizard/src/expression/operation/opfield.cpp
        sparselizard/src/expression/operation/opinversion.cpp
        sparselizard/src/expression/operation/opinvjac.cpp
        sparselizard/src/expression/operation/opjac.cpp
        sparselizard/src/expression/operation/oplog10.cpp
        sparselizard/src/expression/operation/opparameter.cpp
        sparselizard/src/expression/operation/oppower.cpp
        sparselizard/src/expression/operation/opproduct.cpp
        sparselizard/src/expression/operation/opsin.cpp
        sparselizard/src/expression/operation/opsum.cpp
        sparselizard/src/expression/operation/optan.cpp
        sparselizard/src/expression/operation/optf.cpp
        sparselizard/src/expression/operation/optime.cpp


        sparselizard/src/field/coefmanager.cpp
        sparselizard/src/field/field.cpp
        sparselizard/src/field/jacobian.cpp
        sparselizard/src/field/rawfield.cpp


        sparselizard/src/formulation/contribution.cpp
        sparselizard/src/formulation/dofmanager.cpp
        sparselizard/src/formulation/formulation.cpp
        sparselizard/src/formulation/mat.cpp
        sparselizard/src/formulation/rawmat.cpp
        sparselizard/src/formulation/rawvec.cpp
        sparselizard/src/formulation/vec.cpp

        sparselizard/src/gausspoint/gausspoints.cpp
        sparselizard/src/gausspoint/gphexahedron.cpp
        sparselizard/src/gausspoint/gpline.cpp
        sparselizard/src/gausspoint/gppoint.cpp
        sparselizard/src/gausspoint/gpprism.cpp
        sparselizard/src/gausspoint/gppyramid.cpp
        sparselizard/src/gausspoint/gpquadrangle.cpp
        sparselizard/src/gausspoint/gptetrahedron.cpp
        sparselizard/src/gausspoint/gptriangle.cpp


        sparselizard/src/geometry/geotools.cpp
        sparselizard/src/geometry/rawarc.cpp
        sparselizard/src/geometry/rawdisk.cpp
        sparselizard/src/geometry/rawextrusion.cpp
        sparselizard/src/geometry/rawline.cpp
        sparselizard/src/geometry/rawpoint.cpp
        sparselizard/src/geometry/rawquadrangle.cpp
        sparselizard/src/geometry/rawshape.cpp
        sparselizard/src/geometry/rawsurface.cpp
        sparselizard/src/geometry/rawvolume.cpp
        sparselizard/src/geometry/shape.cpp

        sparselizard/src/mesh/disjointregions.cpp
        sparselizard/src/mesh/disjointregionselector.cpp
        sparselizard/src/mesh/elements.cpp
        sparselizard/src/mesh/elementselector.cpp
        sparselizard/src/mesh/mesh.cpp
        sparselizard/src/mesh/myalgorithm.cpp
        sparselizard/src/mesh/mystring.cpp
        sparselizard/src/mesh/nodes.cpp
        sparselizard/src/mesh/physicalregion.cpp
        sparselizard/src/mesh/physicalregions.cpp
        sparselizard/src/mesh/spanningtree.cpp

        sparselizard/src/mesh/gmsh/gmshinterface.cpp

        sparselizard/src/resolution/eigenvalue.cpp
        sparselizard/src/resolution/newmark.cpp

        sparselizard/src/shapefunction/polynomial.cpp

        sparselizard/src/shapefunction/lagrange/lagrangeformfunction.cpp
        sparselizard/src/shapefunction/lagrange/lagrangehexahedron.cpp
        sparselizard/src/shapefunction/lagrange/lagrangeline.cpp
        sparselizard/src/shapefunction/lagrange/lagrangepoint.cpp
        sparselizard/src/shapefunction/lagrange/lagrangeprism.cpp
        sparselizard/src/shapefunction/lagrange/lagrangepyramid.cpp
        sparselizard/src/shapefunction/lagrange/lagrangequadrangle.cpp
        sparselizard/src/shapefunction/lagrange/lagrangetetrahedron.cpp
        sparselizard/src/shapefunction/lagrange/lagrangetriangle.cpp


        sparselizard/src/shapefunction/hierarchical/h1/h1hexahedron.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1line.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1point.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1prism.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1pyramid.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1quadrangle.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1tetrahedron.cpp
        sparselizard/src/shapefunction/hierarchical/h1/h1triangle.cpp
        sparselizard/src/shapefunction/hierarchical/h1/oneconstant.cpp


        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlhexahedron.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlline.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlpoint.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlprism.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlpyramid.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurlquadrangle.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurltetrahedron.cpp
        sparselizard/src/shapefunction/hierarchical/hcurl/hcurltriangle.cpp

        sparselizard/src/shapefunction/hierarchical/meca/h11.cpp
        sparselizard/src/shapefunction/hierarchical/meca/q6.cpp


        sparselizard/src/shapefunction/hierarchical/hierarchicalformfunction.cpp
        sparselizard/src/shapefunction/hierarchical/hierarchicalformfunctioncontainer.cpp
        sparselizard/src/shapefunction/hierarchical/hierarchicalformfunctioniterator.cpp
        sparselizard/src/shapefunction/hierarchical/legendre.cpp
        sparselizard/src/shapefunction/hierarchical/orientation.cpp
        sparselizard/src/shapefunction/hierarchical/selector.cpp

)



add_executable(eigenvalues-elasticity-membrane-3d sparselizard/examples/eigenvalues-elasticity-membrane-3d/main.cpp)

target_link_libraries(eigenvalues-elasticity-membrane-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(elasticity-geometric-nonlinearity-eigenvalues-3d sparselizard/examples/elasticity-geometric-nonlinearity-eigenvalues-3d/main.cpp)

target_link_libraries(elasticity-geometric-nonlinearity-eigenvalues-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(elasticity-membrane-3d sparselizard/examples/elasticity-membrane-3d/main.cpp)

target_link_libraries(elasticity-membrane-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(electromagnetic-waveguide-2d sparselizard/examples/electromagnetic-waveguide-2d/main.cpp)

target_link_libraries(electromagnetic-waveguide-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(electromagnetic-waveguide-3d sparselizard/examples/electromagnetic-waveguide-3d/main.cpp)

target_link_libraries(electromagnetic-waveguide-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(electromagnetic-waveguide-time-resolution-2d sparselizard/examples/electromagnetic-waveguide-time-resolution-2d/main.cpp)

target_link_libraries(electromagnetic-waveguide-time-resolution-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(electromagnetic-waveguide-time-resolution-3d sparselizard/examples/electromagnetic-waveguide-time-resolution-3d/main.cpp)

target_link_libraries(electromagnetic-waveguide-time-resolution-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(electrostatics-1d sparselizard/examples/electrostatics-1d/main.cpp)

target_link_libraries(electrostatics-1d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

add_executable(high-order-interpolations-2d sparselizard/examples/high-order-interpolations-2d/main.cpp)

target_link_libraries(high-order-interpolations-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

add_executable(magnetodynamics-av-induction-3d sparselizard/examples/magnetodynamics-av-induction-3d/main.cpp)

target_link_libraries(magnetodynamics-av-induction-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(magnetostatics-vector-potential-3d sparselizard/examples/magnetostatics-vector-potential-3d/main.cpp)

target_link_libraries(magnetostatics-vector-potential-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )

add_executable(mesher-extruded-mechanical-structure-3d sparselizard/examples/mesher-extruded-mechanical-structure-3d/main.cpp)

target_link_libraries(mesher-extruded-mechanical-structure-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )


add_executable(nonlinear-electro-elasto-acoustic-micromembrane-multiharmonic-2d sparselizard/examples/nonlinear-electro-elasto-acoustic-micromembrane-multiharmonic-2d/main.cpp)

target_link_libraries(nonlinear-electro-elasto-acoustic-micromembrane-multiharmonic-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )




add_executable(nonlinear-electro-thermal-heating-3d sparselizard/examples/nonlinear-electro-thermal-heating-3d/main.cpp)

target_link_libraries(nonlinear-electro-thermal-heating-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )




add_executable(nonlinear-electroelastic-micromembrane-2d sparselizard/examples/nonlinear-electroelastic-micromembrane-2d/main.cpp)

target_link_libraries(nonlinear-electroelastic-micromembrane-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )




add_executable(nonlinear-potentialflow-airfoil-2d sparselizard/examples/nonlinear-potentialflow-airfoil-2d/main.cpp)

target_link_libraries(nonlinear-potentialflow-airfoil-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )



add_executable(piezoelectricity-bilayer-3d sparselizard/examples/piezoelectricity-bilayer-3d/main.cpp)

target_link_libraries(piezoelectricity-bilayer-3d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )



add_executable(pmut-axisymmetry-2d sparselizard/examples/pmut-axisymmetry-2d/main.cpp)

target_link_libraries(pmut-axisymmetry-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )



add_executable(viscousflow-microvalve-2d sparselizard/examples/viscousflow-microvalve-2d/main.cpp)

target_link_libraries(viscousflow-microvalve-2d
        ${MPI_C_LIBRARIES}
        Sparselizard
        petsclib
        mpi
        -lblas
        -lslepc
        )
