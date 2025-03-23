cmake_minimum_required(VERSION 3.13)

project(stratego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.6.1 REQUIRED system window graphics CONFIG)

add_subdirectory(src)
add_subdirectory(include)

install(DIRECTORY font DESTINATION ${CMAKE_BINARY_DIR})
install(DIRECTORY images DESTINATION ${CMAKE_BINARY_DIR})
