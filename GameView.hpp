#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Player.hpp"

class GameView 
{
    Player& playerA;
    Player& playerB;
    sf::Sprite board_border;
    sf::Sprite grass_light;
    sf::Sprite grass_dark;
    sf::Texture board_border_texture;
    sf::Texture grass_light_texture;
    sf::Texture grass_dark_texture;
    // std::map<int, std::string> obstacle_textures;
    std::array<std::pair<sf::Sprite, std::string>, 8> obstacle_sprites;
    std::array<std::pair<sf::Texture, std::string>, 8> obstacle_textures;

    void draw_grass(sf::RenderWindow& win);
    void draw_obstacles(sf::RenderWindow& win);
    public:
    GameView(Player& pA, Player& pB);
    void draw(sf::RenderWindow& win);
};