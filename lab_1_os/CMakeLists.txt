cmake_minimum_required(VERSION 3.10)

project(ParentChildExample C)

set(SOURCES_PARENT parent.c)
set(SOURCES_CHILD child.c)

add_executable(parent ${SOURCES_PARENT})

add_executable(child ${SOURCES_CHILD})

set_property(TARGET parent child PROPERTY C_STANDARD 11)

target_compile_options(parent PRIVATE -Wall -Wextra -Werror)
target_compile_options(child PRIVATE -Wall -Wextra -Werror)

add_dependencies(parent child)
