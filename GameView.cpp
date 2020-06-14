#include "GameView.hpp"

#include <algorithm>

GameView::GameView(Player& pA, Player& pB)
    : playerA(pA),
      playerB(pB) {
    for (int i = 0; i < 8; i++) {
        if (i <= 3) {
            obstacle_textures[i] = (std::pair<sf::Texture, std::string>(sf::Texture(), "lake1_" + std::to_string(i + 1) + ".png"));
        } else {
            obstacle_textures[i] = (std::pair<sf::Texture, std::string>(sf::Texture(), "lake2_" + std::to_string(i - 3) + ".png"));
        }
    }
    for (int i = 0; i < 8; i++) {
        obstacle_sprites[i] = (std::pair<sf::Sprite, std::string>(sf::Sprite(), "lake2_" + std::to_string(i + 1) + ".png"));
    }
    if (!board_border_texture.loadFromFile("/home/wojtek/cpp/Programowanie/Obiektowe/Studia_projekt/stratego/images/board/border_scaled.png")) {
        std::cerr << "board border error loading from file!\n";
        abort();
    }
    if (!grass_light_texture.loadFromFile("/home/wojtek/cpp/Programowanie/Obiektowe/Studia_projekt/stratego/images/board/grass1_scaled.png")) {
        std::cerr << "grass light error loading from file!\n";
        abort();
    }
    if (!grass_dark_texture.loadFromFile("/home/wojtek/cpp/Programowanie/Obiektowe/Studia_projekt/stratego/images/board/grass2_scaled.png")) {
        std::cerr << "grass dark error loading from file!\n";
        abort();
    }
    for (auto& [texture, texture_name] : obstacle_textures) {
        if (!texture.loadFromFile("/home/wojtek/cpp/Programowanie/Obiektowe/Studia_projekt/stratego/images/board/" + texture_name)) {
            std::cerr << texture_name << " error loading from file!\n";
        }
    }
    for (size_t i = 0; i < obstacle_sprites.size(); ++i) {
        obstacle_sprites[i].first.setTexture(obstacle_textures[i].first);
    }

    board_border.setTexture(board_border_texture);
    grass_light.setTexture(grass_light_texture);
    grass_dark.setTexture(grass_dark_texture);
}

void GameView::draw_grass(sf::RenderWindow& win) {
    for (size_t row = 0; row < playerA.get_board().get_height(); ++row) {
        int tile_y_pos = (row + 1) * 64;
        for (size_t col = 0; col < playerA.get_board().get_width(); ++col) {
            int tile_x_pos = (col + 1) * 64;
            grass_light.setPosition(tile_x_pos, tile_y_pos);
            grass_dark.setPosition(tile_x_pos, tile_y_pos);
            if (col % 2) {
                if (row % 2) {
                    win.draw(grass_light);
                } else {
                    win.draw(grass_dark);
                }

            } else {
                if (row % 2) {
                    win.draw(grass_dark);
                } else {
                    win.draw(grass_light);
                }
            }
        }
    }
}

void GameView::draw_obstacles(sf::RenderWindow& win) {
    int i = 0;
    int j = 4;
    for (size_t row = 5; row < 7; ++row) {
        int obstacle_y_pos = 64 * (row + 1);
        for (size_t col = 2; col < 4; ++col) {
            size_t obstacle_x_pos = 64 * (col + 1);
            obstacle_sprites[i].first.setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[i].first);
            i++;
            std::cout << i << "\n";
        }
        for (size_t col = 6; col < 8; ++col) {
            size_t obstacle_x_pos = 64 * (col + 1);
            obstacle_sprites[j].first.setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[j].first);
            j++;
            std::cout << j << "\n";
        }
    }
}

void GameView::draw(sf::RenderWindow& win) {
    win.draw(board_border);
    draw_grass(win);
    draw_obstacles(win);
}