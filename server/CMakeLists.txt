cmake_minimum_required(VERSION 3.10)

project(server)

# todo: if widnows
find_package (Threads REQUIRED)

find_package(Boost 1.65.1 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(util)
include_directories(transport)
include_directories(objects)
include_directories(client)

aux_source_directory(util util_src)
aux_source_directory(transport transport_src)
aux_source_directory(objects objects_src)
aux_source_directory(client client_src)

add_executable(server main.cpp ${util_src} ${transport_src} ${objects_src} ${client_src})

target_link_libraries(server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
