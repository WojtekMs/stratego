#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Player.hpp"

class GameView {
    Player& playerA;
    Player& playerB;
    int TILE_SIZE;
    int X_ADDITIONAL_SPACE;
    sf::Vector2f window_size;
    TURN current_player_turn;
    bool dragging;
    float mouseX;
    float mouseY;
    float mouseObjectOffSetX;
    float mouseObjectOffSetY;
    sf::Sprite* unit_it;

    sf::Sprite board_border;
    sf::Sprite grass_light;
    sf::Sprite grass_dark;
    std::array<sf::Sprite, 13> red_units_sprites;

    sf::Texture board_border_texture;
    sf::Texture grass_light_texture;
    sf::Texture grass_dark_texture;
    std::array<std::pair<sf::Sprite, std::string>, 8> obstacle_sprites;
    std::array<std::pair<sf::Texture, std::string>, 8> obstacle_textures;
    std::array<sf::Texture, 13> red_unit_textures;

    void load_red_units_textures();
    void set_red_units_sprites();
    void draw_grass(sf::RenderWindow& win);
    void draw_obstacles(sf::RenderWindow& win);
    void draw_units_for_init(sf::RenderWindow& win);

public:
    GameView(Player& pA, Player& pB);
    void draw(sf::RenderWindow& win);
    sf::Vector2f get_window_size() { return window_size; };
    void handle_events(sf::Event& event);
};