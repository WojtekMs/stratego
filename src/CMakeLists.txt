add_library(
  stratego-src
  AttackInfoBox.cpp
  BigButton.cpp
  Board.cpp
  Box.cpp
  Button.cpp
  ButtonInterface.cpp
  Game.cpp
  GameController.cpp
  GameView.cpp
  MainMenu.cpp
  Player.cpp
  Attack.cpp
  unit/BombUnit.cpp
  unit/FlagUnit.cpp
  unit/MinerUnit.cpp
  unit/RegularUnit.cpp
  unit/ScoutUnit.cpp
  unit/SpyUnit.cpp
  unit/Unit.cpp
  unit/UnitCounter.cpp
  unit/UnitModel.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(stratego-src PUBLIC sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} stratego-src)
