cmake_minimum_required(VERSION 3.10)

project(stratego)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ../)

find_package(SFML 2 COMPONENTS window graphics audio REQUIRED)

add_compile_options(-Wall -Wextra -Wconversion -pedantic)

add_executable(a.out main.cpp Board.cpp Player.cpp GameView.cpp Button.cpp test.cpp) 

target_link_libraries(a.out sfml-system sfml-window sfml-graphics sfml-audio)

