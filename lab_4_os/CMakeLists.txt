cmake_minimum_required(VERSION 3.10)
project(DynamicLibraries)

# Устанавливаем стандарт C++11
set(CMAKE_CXX_STANDARD 17)

# Добавляем библиотеки
add_library(derivative_first SHARED Lib/src/Func1/derivative_first.cpp)
add_library(derivative_second SHARED Lib/src/Func1/derivative_second.cpp)
add_library(e_formule SHARED Lib/src/Func2/e_formule.cpp)
add_library(e_series SHARED Lib/src/Func2/e_series.cpp)

# Добавляем исполняемые файлы
add_executable(main_compile_time Main1/main1.cpp)
target_link_libraries(main_compile_time derivative_first e_formule)

add_executable(main_runtime Main2/main2.cpp)
