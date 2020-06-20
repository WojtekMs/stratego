#pragma once

#include "GameView.hpp"
#include "GameController.hpp"

class Game
{
    GameView& game_view;
    GameController& game_controller;
    sf::Clock clock;
    bool clock_started;
    void draw(sf::RenderWindow& win);
    public:
    Game(GameView& g_view, GameController& g_controller);
    void run();
};