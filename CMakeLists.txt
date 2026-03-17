cmake_minimum_required(VERSION 4.1)
project(Parallelisme_MPI)
find_package(MPI REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Parallelisme_MPI main.cpp)
target_include_directories(Parallelisme_MPI PRIVATE ${MPI_INCLUDE_PATH})
target_link_libraries(Parallelisme_MPI PRIVATE MPI::MPI_CXX)