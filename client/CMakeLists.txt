cmake_minimum_required(VERSION 3.10)

project(client)

# todo: if widnows
find_package (Threads REQUIRED)

find_package(Boost 1.65.1 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(transport)
aux_source_directory(transport transport_src)

include_directories(objects)
aux_source_directory(objects objects_src)

add_executable(client main.cpp client.cpp ${transport_src} ${objects_src})
target_link_libraries(client ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
