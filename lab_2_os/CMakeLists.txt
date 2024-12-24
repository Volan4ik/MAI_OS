cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MonteCarloSimulation C)

# Указываем исходные файлы
set(SOURCES main.c)

# Создаем исполняемый файл
add_executable(monte_carlo_simulation ${SOURCES})

# Устанавливаем стандарт C
set_property(TARGET monte_carlo_simulation PROPERTY C_STANDARD 11)

# Добавляем опции компиляции
target_compile_options(monte_carlo_simulation PRIVATE -Wall -Wextra -Werror)

# Указываем, что нужно использовать библиотеку pthread
target_link_libraries(monte_carlo_simulation pthread)
