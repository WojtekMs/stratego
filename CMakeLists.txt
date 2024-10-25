cmake_minimum_required(VERSION 3.13)

project(stratego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  stratego-src
  src/AttackInfoBox.cpp
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

target_include_directories(stratego-src PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(SFML 2.6.1 REQUIRED system window graphics CONFIG)

target_link_libraries(stratego-src PUBLIC sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} stratego-src)

install(DIRECTORY font DESTINATION ${CMAKE_BINARY_DIR})
install(DIRECTORY images DESTINATION ${CMAKE_BINARY_DIR})
