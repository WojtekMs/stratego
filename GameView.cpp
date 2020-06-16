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
      unit_it(nullptr),
      sprite_initial_position(-1, -1),
      unit_chosen(true),
      done_button("brak") {
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
    if (!font.loadFromFile("font/chandas1-2.ttf")) {
        std::cerr << "font loading failed!\n";
        abort();
    }
    text.setFont(font);

    load_red_units_textures();
    set_red_units_sprites();
    board_border.setTexture(board_border_texture);
    grass_light.setTexture(grass_light_texture);
    grass_dark.setTexture(grass_dark_texture);
}

void GameView::load_blue_units_textures() {
    for(size_t i = 0; i < 9; ++i) {
        if(!blue_unit_textures[i].loadFromFile("images/pieces/blue/blue_" + std::to_string(i + 2) + ".png")) {
            std::cerr << "blue unit" + std::to_string(i + 2) + "failed to load a texture!\n";
            abort();
        }
    }
    if (!blue_unit_textures[9].loadFromFile("images/pieces/blue/blue_bomb.png")) {
        std::cerr << "blue bomb loading texture failed! \n";
        abort();      
    }
     if (!blue_unit_textures[10].loadFromFile("images/pieces/blue/blue_flag.png")) {
        std::cerr << "blue flag loading texture failed! \n";
        abort();
    }
    if (!blue_unit_textures[11].loadFromFile("images/pieces/blue/blue_spy.png")) {
        std::cerr << "blue spy loading texture failed! \n";
        abort();
    }
    if (!blue_back_texture.loadFromFile("images/pieces/blue/blue_back.png")) {
        std::cerr << "blue back loading texture failed! \n";
        abort();
    }
}

void GameView::set_blue_units_sprites() {
    for (size_t i = 0; i < blue_units_sprites.size(); ++i) {
        blue_units_sprites[i].setTexture(blue_unit_textures[i]);
    }
    blue_back_sprite.setTexture(blue_back_texture);
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
    if (!red_back_texture.loadFromFile("images/pieces/red/red_back.png")) {
        std::cerr << "red back loading texture failed! \n";
        abort();
    }
}

void GameView::set_red_units_sprites() {
    for (size_t i = 0; i < red_units_sprites.size(); ++i) {
        red_units_sprites[i].setTexture(red_unit_textures[i]);
    }
    red_back_sprite.setTexture(red_back_texture);
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

    if (current_player_turn == TURN::PLAYER_A) {
        draw_red_init_units(win);
    } else {
        //draw blue init units
    }
}

void GameView::draw_red_init_units(sf::RenderWindow& win) {
    const int x_denting = board_border.getGlobalBounds().width;
    const int y_denting = TILE_SIZE;
    int col_count = 0;
    int row_count = 0;
    int i = 0;
    for (auto& elem : red_units_sprites) {
        if (i != 0 && i % 4 == 0) {
            col_count = 0;
            row_count++;
        }
        elem.setPosition(x_denting + 2 * col_count * TILE_SIZE, y_denting + row_count * TILE_SIZE);
        text.setPosition(x_denting + TILE_SIZE + 2 * col_count * TILE_SIZE, y_denting + TILE_SIZE / 4 + row_count * TILE_SIZE);
        text.setString("x" + std::to_string(playerA.get_board().get_max_unit_count(i) - playerA.get_units_count(i)));
        if (dragging == true) {
            if (unit_it) {
                unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
            }
        }
        win.draw(elem);
        win.draw(text);
        col_count++;
        i++;
    }
}

void GameView::draw_board(sf::RenderWindow& win) {
    int object_x_pos = -1;
    int object_y_pos = -1;
    int unit_idx = -1;
    Player* player = nullptr;
    if (current_player_turn == TURN::PLAYER_A) {
        player = &playerA;
    }
    if (current_player_turn == TURN::PLAYER_B) {
        player = &playerB;
    }
    if (player == nullptr) {
        return;
    }
    for (int row = 0; row < player->get_board().get_height(); ++row) {
        object_y_pos = (row + 1) * TILE_SIZE;
        for (int col = 0; col < player->get_board().get_width(); ++col) {
            object_x_pos = (col + 1) * TILE_SIZE;
            if (player->get_tile_info(col, row) == "regular") {
                unit_idx = player->get_board().get_unit(col, row)->get_value() - 2;
                draw_red_sprite(win, unit_idx, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "scout") {
                draw_red_sprite(win, 0, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "miner") {
                draw_red_sprite(win, 1, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "bomb") {
                draw_red_sprite(win, 9, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "flag") {
                draw_red_sprite(win, 10, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "spy") {
                draw_red_sprite(win, 11, object_x_pos, object_y_pos);
            }
            if (player->get_tile_info(col, row) == "enemy") {
                // draw blue back
            }
        }
    }
}

void GameView::draw_red_sprite(sf::RenderWindow& win, int idx, int sprite_pos_x, int sprite_pos_y) {
    //needs to be changed -> draw_sprite (add argument TURN player)

    sprite_initial_position = red_units_sprites[idx].getPosition();
    red_units_sprites[idx].setPosition(sprite_pos_x, sprite_pos_y);
    win.draw(red_units_sprites[idx]);
    red_units_sprites[idx].setPosition(sprite_initial_position);
}

void GameView::draw(sf::RenderWindow& win) {
    win.draw(board_border);
    draw_grass(win);
    draw_obstacles(win);
    draw_units_for_init(win);
    draw_board(win);
}

void GameView::handle_events(sf::Event& event) {
    Player* player = nullptr;
    if (current_player_turn == TURN::PLAYER_A) {
        player = &playerA;
    } else {
        player = &playerB;
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        drag_red_player(event);
        change_init_turn(event, player);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        set_unit(event, player);
    }
    if (event.type == sf::Event::MouseMoved) {
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;
    }
}

void GameView::drag_red_player(sf::Event& event) {
    unit_it = std::find_if(red_units_sprites.begin(), red_units_sprites.end(),
                           [&event](const sf::Sprite& unit_sprite) {
                               return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                           });
    if (unit_it != red_units_sprites.end()) {
        dragging = true;
        unit_chosen = true;
        mouseObjectOffSetX = event.mouseButton.x - unit_it->getGlobalBounds().left;
        mouseObjectOffSetY = event.mouseButton.y - unit_it->getGlobalBounds().top;
    }
}

void GameView::change_init_turn(sf::Event& event, Player* player) {
    if (done_button.contains(event.mouseButton.x, event.mouseButton.y)) {
        if (player->get_board().get_state() == STATE::INITIALIZED) {
            current_player_turn = TURN::PLAYER_B;
            playerB.update_board(playerA.get_board());
        }
    }
}

void GameView::set_unit(sf::Event& event, Player* player) {
    dragging = false;
    int col = -1;
    int row = -1;
    col = (event.mouseButton.x - 64) / TILE_SIZE;
    row = (event.mouseButton.y - 64) / TILE_SIZE;
    int idx = unit_it - &red_units_sprites[0];
    if (unit_chosen == true && player->get_units_count(idx) < player->get_board().get_max_unit_count(idx)) {
        if (current_player_turn == TURN::PLAYER_A) {
            player->set_unit(col, row, idx);
        } else {
            //blue units
        }
        unit_chosen = false;
    }
}