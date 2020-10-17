cmake_minimum_required(VERSION 3.1)

project(stratego)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)


set(SRC src/AttackInfoBox.cpp
        src/BigButton.cpp
        src/Board.cpp
        src/Box.cpp
        src/Button.cpp
        src/ButtonInterface.cpp 
        src/Game.cpp 
        src/GameController.cpp 
        src/GameView.cpp 
        src/MainMenu.cpp 
        src/Movable.cpp 
        src/Player.cpp)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

add_library(src ${SRC})
add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(include)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} src sfml-graphics sfml-window sfml-system)
