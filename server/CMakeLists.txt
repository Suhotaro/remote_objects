cmake_minimum_required(VERSION 3.10)

project(server)

# todo: if widnows
find_package (Threads REQUIRED)

find_package(Boost 1.65.1 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(transport)
aux_source_directory(transport transport_src)

add_executable(server main.cpp ${transport_src})
target_link_libraries(server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
