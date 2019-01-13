cmake_minimum_required(VERSION  3.5.1)
project(misc)

add_compile_options(-std=c++14)


include_directories(
        include
)

add_library(
        ${PROJECT_NAME}
        src/traces.cpp
)
