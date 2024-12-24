cmake_minimum_required(VERSION 3.10)

# Укажите имя проекта
project(DistributedSystem)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к заголовочным файлам ZeroMQ
include_directories(/opt/homebrew/include)

# Укажите путь к библиотекам ZeroMQ
link_directories(/opt/homebrew/lib)

# Используйте pkg-config для поиска ZeroMQ
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)

# Добавьте исходные файлы
set(SOURCES
    message.cpp
)

# Добавьте исполняемый файл для сервера
add_executable(server server.cpp ${SOURCES})
target_link_libraries(server ${ZeroMQ_LIBRARIES})

# Добавьте исполняемый файл для клиента
add_executable(client client.cpp ${SOURCES})
target_link_libraries(client ${ZeroMQ_LIBRARIES})