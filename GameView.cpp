#include "GameView.hpp"

#include <algorithm>

GameView::GameView(Player& pA, Player& pB)
    : playerA(pA),
      playerB(pB),
      TILE_SIZE(64),
      X_ADDITIONAL_SPACE(512),
      window_size(12 * TILE_SIZE + X_ADDITIONAL_SPACE, 14 * TILE_SIZE),
      current_player_turn(TURN::PLAYER_A),
      dragging(false),
      mouseX(0),
      mouseY(0),
      mouseObjectOffSetX(0),
      mouseObjectOffSetY(0),
      unit_it(nullptr) {
    for (size_t i = 0; i < obstacle_textures.size(); i++) {
        if (i <= 3) {
            obstacle_textures[i] = (std::pair<sf::Texture, std::string>(sf::Texture(), "lake1_" + std::to_string(i + 1) + ".png"));
        } else {
            obstacle_textures[i] = (std::pair<sf::Texture, std::string>(sf::Texture(), "lake2_" + std::to_string(i - 3) + ".png"));
        }
    }
    for (size_t i = 0; i < obstacle_sprites.size(); i++) {
        obstacle_sprites[i] = (std::pair<sf::Sprite, std::string>(sf::Sprite(), "lake2_" + std::to_string(i + 1) + ".png"));
    }

    if (!board_border_texture.loadFromFile("images/board/border_scaled.png")) {
        std::cerr << "board border error loading from file!\n";
        abort();
    }
    if (!grass_light_texture.loadFromFile("images/board/grass1_scaled.png")) {
        std::cerr << "grass light error loading from file!\n";
        abort();
    }
    if (!grass_dark_texture.loadFromFile("images/board/grass2_scaled.png")) {
        std::cerr << "grass dark error loading from file!\n";
        abort();
    }
    for (auto& [texture, texture_name] : obstacle_textures) {
        if (!texture.loadFromFile("images/board/" + texture_name)) {
            std::cerr << texture_name << " error loading from file!\n";
        }
    }
    for (size_t i = 0; i < obstacle_sprites.size(); ++i) {
        obstacle_sprites[i].first.setTexture(obstacle_textures[i].first);
    }

    load_red_units_textures();
    set_red_units_sprites();
    board_border.setTexture(board_border_texture);
    grass_light.setTexture(grass_light_texture);
    grass_dark.setTexture(grass_dark_texture);
}

void GameView::load_red_units_textures() {
    for (size_t i = 0; i < 9; ++i) {  //only numeric red units textures are loaded
        if (!red_unit_textures[i].loadFromFile("images/pieces/red/red_" + std::to_string(i + 2) + ".png")) {
            std::cerr << "red unit" + std::to_string(i + 2) + " failed to load a texture!\n";
            abort();
        }
    }
    if (!red_unit_textures[9].loadFromFile("images/pieces/red/red_bomb.png")) {
        std::cerr << "red bomb loading texture failed! \n";
        abort();
    }
    if (!red_unit_textures[10].loadFromFile("images/pieces/red/red_flag.png")) {
        std::cerr << "red flag loading texture failed! \n";
        abort();
    }
    if (!red_unit_textures[11].loadFromFile("images/pieces/red/red_spy.png")) {
        std::cerr << "red spy loading texture failed! \n";
        abort();
    }
    if (!red_unit_textures[12].loadFromFile("images/pieces/red/red_back.png")) {
        std::cerr << "red back loading texture failed! \n";
        abort();
    }
}

void GameView::set_red_units_sprites() {
    for (size_t i = 0; i < red_units_sprites.size(); ++i) {
        red_units_sprites[i].setTexture(red_unit_textures[i]);
    }
}

void GameView::draw_grass(sf::RenderWindow& win) {
    for (size_t row = 0; row < playerA.get_board().get_height(); ++row) {
        int tile_y_pos = (row + 1) * TILE_SIZE;
        for (size_t col = 0; col < playerA.get_board().get_width(); ++col) {
            int tile_x_pos = (col + 1) * TILE_SIZE;
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
        int obstacle_y_pos = TILE_SIZE * (row + 1);
        for (size_t col = 2; col < 4; ++col) {
            size_t obstacle_x_pos = TILE_SIZE * (col + 1);
            obstacle_sprites[i].first.setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[i].first);
            i++;
        }
        for (size_t col = 6; col < 8; ++col) {
            size_t obstacle_x_pos = TILE_SIZE * (col + 1);
            obstacle_sprites[j].first.setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[j].first);
            j++;
        }
    }
}

void GameView::draw_units_for_init(sf::RenderWindow& win) {
    if (current_player_turn == TURN::PLAYER_A) {
        if (playerA.get_board().get_state() == STATE::INITIALIZED) {
            return;
        }
    }
    if (current_player_turn == TURN::PLAYER_B) {
        if (playerB.get_board().get_state() == STATE::INITIALIZED) {
            return;
        }
    }
    const int x_denting = board_border.getGlobalBounds().width + TILE_SIZE;
    const int y_denting = TILE_SIZE;

    int j = 0;
    int k = 0;
    if (current_player_turn == TURN::PLAYER_A) {
        for (size_t i = 0; i < red_units_sprites.size() - 1; ++i) {
            if (i != 0 && i % 4 == 0) {
                j = 0;
                k++;
            }
            if (dragging == false) {
                red_units_sprites[i].setPosition(x_denting + j * TILE_SIZE, y_denting + k * TILE_SIZE);
            } else {
                if (unit_it) {
                    unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
                }
            }
            win.draw(red_units_sprites[i]);
            j++;
        }
    }
    // red_bomb_sprite.setPosition(x_denting + j * TILE_SIZE, y_denting + k * TILE_SIZE);
    // win.draw(red_bomb_sprite);
    // j++;
    // red_spy_sprite.setPosition(x_denting + j * TILE_SIZE, y_denting + k * TILE_SIZE);
    // win.draw(red_spy_sprite);
    // j++;
    // if (dragging == false) {
    //     red_flag_sprite.setPosition(x_denting + j * TILE_SIZE, y_denting + k * TILE_SIZE);
    // }
    // } else {
    //     red_flag_sprite.setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
    // }
    //     win.draw(red_flag_sprite);
    // } else {
    //     // blue units draw
    // }
}

void GameView::draw(sf::RenderWindow& win) {
    win.draw(board_border);
    draw_grass(win);
    draw_obstacles(win);
    draw_units_for_init(win);
}

void GameView::handle_events(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        std::cout << "mouseX: " << mouseX << ", mouseY: " << mouseY << '\n';
        unit_it = std::find_if(red_units_sprites.begin(), red_units_sprites.end(),
                               [&event](const sf::Sprite& unit_sprite) {
                                   return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                               });
        if (unit_it != red_units_sprites.end()) {
            dragging = true;
            mouseObjectOffSetY = event.mouseButton.x - unit_it->getGlobalBounds().left;
            mouseObjectOffSetX = event.mouseButton.y - unit_it->getGlobalBounds().top;
            // std::cout << "mouseX: " << mouseX << ", mouseY: " << mouseY << '\n';
            // unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
            // std::cout << "unit_it_x: " << unit_it->getPosition().x << ", unit_it_y: " << unit_it->getPosition().y << "\n";
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        dragging = false;
    }
    if (event.type == sf::Event::MouseMoved) {
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;
        // std::cout << "mouseX: " << mouseX << ", mouseY: " << mouseY << '\n';
    }
    // if (unit_it) {
    // unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
    // std::cout << "unit_it_x: " << unit_it->getPosition().x << ", unit_it_y: " << unit_it->getPosition().y << "\n";

    // }
    // if (dragging == true) {
    // if (unit_it) {
    // unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
    // }

    // }
}