cmake_minimum_required(VERSION 3.10)

project(DAGScheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(dag_scheduler main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(dag_scheduler Threads::Threads)
