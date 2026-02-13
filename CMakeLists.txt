cmake_minimum_required(VERSION 3.10)

project(rayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(rayTracer src/main.cc)
target_include_directories(rayTracer PRIVATE src)
target_link_libraries(rayTracer PRIVATE Threads::Threads)

# High performance flags for Release only
target_compile_options(rayTracer PRIVATE
    $<$<CONFIG:Release>:-O3 -march=native -DNDEBUG>
)

# Enable LTO (flto) for Release
set_property(TARGET rayTracer PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)