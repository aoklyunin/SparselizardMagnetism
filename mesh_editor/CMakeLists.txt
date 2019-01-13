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


set(JSONCPP_LIBRARIES jsoncpp)


include_directories(
        include
        ../misc/include
        ../sparselizard_lib/sparselizard/src
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
        misc
        ${CMAKE_THREAD_LIBS_INIT}
        ${JSONCPP_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        -lboost_filesystem
        -lboost_system
        #-fsanitize=address
        )

