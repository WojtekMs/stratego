#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class GameView 
{
    Player& playerA;
    Player& playerB;
    sf::Sprite board_border;
    sf::Texture board_border_texture;

    public:
    GameView(Player& pA, Player& pB);
    void draw(sf::RenderWindow& win);
};