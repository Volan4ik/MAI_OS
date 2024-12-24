cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ProcessCommunication C)

# Указываем стандарт C
set(CMAKE_C_STANDARD 11)

# Добавляем флаги компиляции
add_compile_options(-Wall -Wextra -Werror)
add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter)


# Указываем исходные файлы
set(CHILD_SOURCE child.c)
set(PARENT_SOURCE parent.c)

# Создаем два исполняемых файла: parent и child
add_executable(parent ${PARENT_SOURCE})
add_executable(child ${CHILD_SOURCE})

# Указываем дополнительные библиотеки (например, для работы с сигналами и mmap)
target_link_libraries(parent m)
target_link_libraries(child m)
