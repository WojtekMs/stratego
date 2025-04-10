#pragma once

#include "GameController.hpp"
#include "GameView.hpp"
#include "cScreen.hpp"

class Game : public cScreen {
  GameView &game_view;
  GameController &game_controller;
  sf::Clock clock;
  bool clock_started;
  void draw(sf::RenderWindow &win);

public:
  Game(GameView &g_view, GameController &g_controller);
  std::string run(sf::RenderWindow &win) override;
};