#include "GameView.hpp"

#include <algorithm>

// #include "Unit.hpp"
#include "Player.hpp"

GameView::GameView(Player& pA, Player& pB)
    : playerA(pA),
      playerB(pB),
      TILE_SIZE(64),
      X_ADDITIONAL_SPACE(512),
      window_size(12 * TILE_SIZE + X_ADDITIONAL_SPACE, 14 * TILE_SIZE),
      current_player_turn(TURN::PLAYER_B),
      dragging(false),
      mouseX(0),
      mouseY(0),
      mouseObjectOffSetX(0),
      mouseObjectOffSetY(0),
      unit_it(nullptr),
      sprite_initial_position(-1, -1),
      board_a_initialized(false),
      board_b_initialized(false),
      active_unit(-1, -1),
      is_active_unit(false),
      hovering_tile(-1, -1),
      current_player(&playerB),
      other_player(&playerA),
      unit_moved_this_round(false),
      done_button("Done"),
      remove_button("Remove"),
      end_turn_button("End Turn"),
      board_textures_path("images/board/"),
      pieces_textures_path("images/pieces/"),
      global_game_state(GAME_STATE::BOARDS_NOT_SET),
      local_game_state(GAME_STATE::BOARDS_NOT_SET) {
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

    // if (!white_highlight_texture.loadFromFile("images/board/highlight_white.png")) {
    //     std::cerr << "white highlight texture failed! \n";
    //     abort();
    // }
    text.setFont(font);

    // white_highlight_sprite.setTexture(white_highlight_texture);

    load_red_units_textures();
    load_blue_units_textures();
    load_highlight_textures();
    set_red_units_sprites();
    set_blue_units_sprites();
    set_highlight_sprites();
    board_border.setTexture(board_border_texture);
    grass_light.setTexture(grass_light_texture);
    grass_dark.setTexture(grass_dark_texture);
}

void GameView::load_highlight_textures() {
    if (!red_highlight_texture.loadFromFile(board_textures_path + "highlight_red.png")) {
        std::cerr << "red highlight texture failed!\n";
        abort();
    }
    if (!yellow_highlight_texture.loadFromFile(board_textures_path + "highlight_yellow.png")) {
        std::cerr << "yellow highlight texture failed!\n";
        abort();
    }
    if (!green_highlight_texture.loadFromFile(board_textures_path + "highlight_green.png")) {
        std::cerr << "green highlight texture failed!\n";
        abort();
    }
}

void GameView::set_highlight_sprites() {
    yellow_highlight_sprite.setTexture(yellow_highlight_texture);
    green_highlight_sprite.setTexture(green_highlight_texture);
    red_highlight_sprite.setTexture(red_highlight_texture);
}

void GameView::load_blue_units_textures() {
    for (size_t i = 0; i < 9; ++i) {
        if (!blue_unit_textures[i].loadFromFile("images/pieces/blue/blue_" + std::to_string(i + 2) + ".png")) {
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
    for (int row = 0; row < playerA.get_board().get_height(); ++row) {
        int tile_y_pos = (row + 1) * TILE_SIZE;
        for (int col = 0; col < playerA.get_board().get_width(); ++col) {
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
        if (board_a_initialized) {
            return;
        }
    }
    if (current_player_turn == TURN::PLAYER_B) {
        if (board_b_initialized) {
            return;
        }
    }

    if (current_player_turn == TURN::PLAYER_A) {
        draw_red_init_units(win);
    } else {
        draw_blue_init_units(win);
    }
    draw_done_button(win);
    if (is_active_unit) {
        draw_remove_button(win);
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

void GameView::draw_blue_init_units(sf::RenderWindow& win) {
    const int x_denting = board_border.getGlobalBounds().width;
    const int y_denting = TILE_SIZE;
    int col_count = 0;
    int row_count = 0;
    for (size_t i = 0; i < blue_units_sprites.size(); ++i) {
        if (i != 0 && i % 4 == 0) {
            col_count = 0;
            row_count++;
        }
        blue_units_sprites[i].setPosition(x_denting + 2 * col_count * TILE_SIZE, y_denting + row_count * TILE_SIZE);
        text.setPosition(x_denting + TILE_SIZE + 2 * col_count * TILE_SIZE, y_denting + TILE_SIZE / 4 + row_count * TILE_SIZE);
        text.setString("x" + std::to_string(playerB.get_board().get_max_unit_count(i) - playerB.get_units_count(i)));
        if (dragging == true) {
            if (unit_it) {
                unit_it->setPosition(mouseX - mouseObjectOffSetX, mouseY - mouseObjectOffSetY);
            }
        }
        win.draw(blue_units_sprites[i]);
        win.draw(text);
        col_count++;
    }
}

void GameView::draw_done_button(sf::RenderWindow& win) {
    const int x_denting = board_border.getGlobalBounds().width;
    done_button.set_position(x_denting + (X_ADDITIONAL_SPACE - done_button.get_width()) / 2, TILE_SIZE * 6);
    // done_button.set_text("Done");
    done_button.draw(win);
}

void GameView::draw_remove_button(sf::RenderWindow& win) {
    remove_button.set_position(done_button.get_position().x, done_button.get_position().y + done_button.get_height() + TILE_SIZE);
    remove_button.draw(win);
}

void GameView::draw_board(sf::RenderWindow& win) {
    int object_x_pos = -1;
    int object_y_pos = -1;
    int unit_idx = -1;
    for (int row = 0; row < current_player->get_board().get_height(); ++row) {
        object_y_pos = (row + 1) * TILE_SIZE;
        for (int col = 0; col < current_player->get_board().get_width(); ++col) {
            object_x_pos = (col + 1) * TILE_SIZE;
            if (current_player->get_tile_info(col, row) == "regular") {
                unit_idx = current_player->get_board().get_unit(col, row)->get_value() - 2;
                draw_sprite(win, unit_idx, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "scout") {
                draw_sprite(win, 0, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "miner") {
                draw_sprite(win, 1, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "bomb") {
                draw_sprite(win, 9, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "flag") {
                draw_sprite(win, 10, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "spy") {
                draw_sprite(win, 11, object_x_pos, object_y_pos);
            }
            if (current_player->get_tile_info(col, row) == "enemy") {
                draw_sprite(win, 12, object_x_pos, object_y_pos);
            }
            if (active_unit.x == col && active_unit.y == row) {
                yellow_highlight_sprite.setPosition(return_pixels(col, row));
                win.draw(yellow_highlight_sprite);
            }
            if (board_b_initialized && board_a_initialized) {
                end_turn_button.set_position(done_button.get_position());
                end_turn_button.draw(win);
            }
        }
    }
}

void GameView::draw_sprite(sf::RenderWindow& win, int idx, int sprite_pos_x, int sprite_pos_y) {
    if (idx == 12) {
        if (current_player_turn == TURN::PLAYER_A) {
            blue_back_sprite.setPosition(sprite_pos_x, sprite_pos_y);
            win.draw(blue_back_sprite);
        } else {
            red_back_sprite.setPosition(sprite_pos_x, sprite_pos_y);
            win.draw(red_back_sprite);
        }
    } else {
        if (current_player_turn == TURN::PLAYER_A) {
            sprite_initial_position = red_units_sprites[idx].getPosition();
            red_units_sprites[idx].setPosition(sprite_pos_x, sprite_pos_y);
            win.draw(red_units_sprites[idx]);
            red_units_sprites[idx].setPosition(sprite_initial_position);
        } else {
            sprite_initial_position = blue_units_sprites[idx].getPosition();
            blue_units_sprites[idx].setPosition(sprite_pos_x, sprite_pos_y);
            win.draw(blue_units_sprites[idx]);
            blue_units_sprites[idx].setPosition(sprite_initial_position);
        }
    }
}

void GameView::draw_possible_moves_for_active_unit(sf::RenderWindow& win) {
    if (!board_a_initialized && !board_b_initialized) {
        return;
    }
    if (!is_active_unit) {
        return;
    }
    if (!current_player->get_board().get_unit(active_unit.x, active_unit.y)) {
        return;
    }
    if (!unit_moved_this_round) {
        if (current_player->get_board().get_unit(active_unit.x, active_unit.y)->get_type() == "scout") {
            highlight_scout_moves(win);
        } else {
            highlight_regular_moves(win);
        }
    }
}

void GameView::highlight_regular_moves(sf::RenderWindow& win) {
    highlight_tile(win, active_unit.x - 1, active_unit.y);
    highlight_tile(win, active_unit.x + 1, active_unit.y);
    highlight_tile(win, active_unit.x, active_unit.y + 1);
    highlight_tile(win, active_unit.x, active_unit.y - 1);
    // if (check_if_viable(active_unit, active_unit.x - 1, active_unit.y)) {
    //     green_highlight_sprite.setPosition(return_pixels(active_unit.x - 1, active_unit.y));
    //     win.draw(green_highlight_sprite);
    // }

    // if (check_if_viable(active_unit, active_unit.x + 1, active_unit.y)) {
    //     green_highlight_sprite.setPosition(return_pixels(active_unit.x + 1, active_unit.y));
    //     win.draw(green_highlight_sprite);
    // }
    // if (check_if_viable(active_unit, active_unit.x, active_unit.y + 1)) {
    //     green_highlight_sprite.setPosition(return_pixels(active_unit.x, active_unit.y + 1));
    //     win.draw(green_highlight_sprite);
    // }
    // if (check_if_viable(active_unit, active_unit.x, active_unit.y - 1)) {
    //     green_highlight_sprite.setPosition(return_pixels(active_unit.x, active_unit.y - 1));
    //     win.draw(green_highlight_sprite);
    // }
}

void GameView::highlight_scout_moves(sf::RenderWindow& win) {
    for (int col = active_unit.x + 1; col < current_player->get_board().get_width(); ++col) {
        if (!highlight_tile(win, col, active_unit.y)) {
            break;
        }
    }
    for (int col = active_unit.x - 1; col >= 0; --col) {
        if (!highlight_tile(win, col, active_unit.y)) {
            break;
        }
    }
    for (int row = active_unit.y + 1; row < current_player->get_board().get_height(); ++row) {
        if (!highlight_tile(win, active_unit.x, row)) {
            break;
        }
    }
    for (int row = active_unit.y - 1; row >= 0; --row) {
        if (!highlight_tile(win, active_unit.x, row)) {
            break;
        }
    }
}

bool GameView::highlight_tile(sf::RenderWindow& win, int to_x, int to_y) {
    if (check_if_viable(active_unit, to_x, to_y)) {
        if (current_player->get_tile_info(to_x, to_y) == "enemy") {
            red_highlight_sprite.setPosition(return_pixels(to_x, to_y));
            win.draw(red_highlight_sprite);
            return false;
        } else {
            green_highlight_sprite.setPosition(return_pixels(to_x, to_y));
            win.draw(green_highlight_sprite);
        }
        return true;
    }
    return false;
}

bool GameView::check_if_viable(Board::Tile from, int to_x, int to_y) {
    return current_player->can_move(from, Board::Tile(to_x, to_y));
}

void GameView::draw(sf::RenderWindow& win) {
    win.draw(board_border);
    draw_grass(win);
    draw_obstacles(win);
    draw_units_for_init(win);
    draw_board(win);
    draw_possible_moves_for_active_unit(win);
}

void GameView::handle_events(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        // switch (global_game_state) {
        // case GAME_STATE::BOARDS_NOT_SET:
        handle_initialization(event);
        set_active_unit(event);
        // break;
        // case GAME_STATE::BOTH_BOARDS_SET:
        change_player_turn();
        move_active_unit(event);
        // break;
        // case GAME_STATE::GAME_FINISHED:
        // return;
        // default:
        // break;
        // }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (global_game_state == GAME_STATE::BOARDS_NOT_SET) {
            set_unit(event);
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;
        set_button_highlights(mouseX, mouseY);
        // set_hovering_tile(mouseX, mouseY);
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            TEST_SET_RANDOM_UNITS();
        }
    }
}

void GameView::TEST_SET_RANDOM_UNITS() {
    while (current_player->get_board().get_state() != STATE::FULL) {
        for (int row = 8; row < current_player->get_board().get_height(); ++row) {
            for (int col = 0; col < current_player->get_board().get_width(); ++col) {
                int idx = rand() % 12;
                if (current_player->get_units_count(idx) < current_player->get_board().get_max_unit_count(idx))
                    current_player->set_unit(col, row, idx);
            }
        }
    }
}
void GameView::move_active_unit(sf::Event& event) {
    Board::Tile chosen_tile(return_tile(event.mouseButton.x, event.mouseButton.y));
    std::cout << "chosen tile at the beggining: " << chosen_tile.x << ", " << chosen_tile.y << "\n";
    if (!is_active_unit) {
        return;
    }
    if (!(board_b_initialized || board_a_initialized)) {
        return;
    }
    if (unit_moved_this_round) {
        std::cout << "unit already moved this round!\n";
        return;
    }
    if (!current_player->can_move(active_unit, chosen_tile)) {
        std::cout << "active unit inside can move: " << active_unit.x << ", " << active_unit.y << '\n';
        std::cout << "this unit cant move to this tile!\n";
        return;
    }
    if (current_player->get_tile_info(chosen_tile) == "enemy") {
        local_game_state = GAME_STATE::UNIT_ATTACKED;
        switch (current_player->attack(active_unit, chosen_tile)) {
        case RESULT::WON:
            std::cout << chosen_tile.x << ", " << chosen_tile.y << "\n";
            current_player->remove_unit(chosen_tile);
            other_player->reverse_remove_unit(chosen_tile);
            break;
        case RESULT::DRAW:
            current_player->remove_unit(active_unit);
            current_player->remove_unit(chosen_tile);
            other_player->reverse_remove_unit(active_unit);
            other_player->reverse_remove_unit(chosen_tile);
            active_unit.set_cords(-1, -1);
            break;
        case RESULT::LOST:
            current_player->remove_unit(active_unit);
            other_player->reverse_remove_unit(active_unit);
            active_unit.set_cords(-1, -1);
            break;
        }
        unit_moved_this_round = true;
    }
    if (current_player->move_unit(active_unit, chosen_tile)) {
        local_game_state = GAME_STATE::UNIT_MOVED;
        std::cout << "current: " << static_cast<int>(current_player->get_player_number()) << '\n';
        std::cout << "other: " << static_cast<int>(other_player->get_player_number()) << '\n';
        other_player->reverse_move_unit(active_unit, chosen_tile);
        unit_moved_this_round = true;
        active_unit.set_cords(-1, -1);
    }
}

// void GameView::set_hovering_tile(int mouse_x, int mouse_y) {
//     if (playerA.get_tile_info(return_tile(mouse_x, mouse_y).x, return_tile(mouse_x, mouse_y).y) == "#") {
//         hovering_tile.set_cords(-1, -1);
//     }
//     hovering_tile.set_cords(return_tile(mouse_x, mouse_y));
// }

void GameView::handle_initialization(sf::Event& event) {
    if (board_a_initialized && board_b_initialized) {
        global_game_state = GAME_STATE::BOTH_BOARDS_SET;
        return;
    }
    if (current_player_turn == TURN::PLAYER_A) {
        drag_red_player(event);
    } else {
        drag_blue_player(event);
    }
    remove_unit();
    change_init_turn(event);
}

void GameView::remove_unit() {
    if (board_b_initialized && board_a_initialized) {
        return;
    }
    if (is_active_unit && remove_button.is_highlighted()) {
        current_player->remove_unit(active_unit.x, active_unit.y);
        active_unit.set_cords(-1, -1);
    }
}

void GameView::set_button_highlights(int mouse_x, int mouse_y) {
    if (done_button.contains(mouse_x, mouse_y)) {
        done_button.highlight_on();
    } else {
        done_button.highlight_off();
    }
    if (remove_button.contains(mouse_x, mouse_y)) {
        remove_button.highlight_on();
    } else {
        remove_button.highlight_off();
    }
    if (end_turn_button.contains(mouse_x, mouse_y)) {
        end_turn_button.highlight_on();
    } else {
        end_turn_button.highlight_off();
    }
}

void GameView::drag_red_player(sf::Event& event) {
    unit_it = std::find_if(red_units_sprites.begin(), red_units_sprites.end(),
                           [&event](const sf::Sprite& unit_sprite) {
                               return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                           });
    if (unit_it != red_units_sprites.end()) {
        dragging = true;
        mouseObjectOffSetX = event.mouseButton.x - unit_it->getGlobalBounds().left;
        mouseObjectOffSetY = event.mouseButton.y - unit_it->getGlobalBounds().top;
    }
}

void GameView::drag_blue_player(sf::Event& event) {
    unit_it = std::find_if(blue_units_sprites.begin(), blue_units_sprites.end(),
                           [&event](const sf::Sprite& unit_sprite) {
                               return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                           });
    if (unit_it != blue_units_sprites.end()) {
        dragging = true;
        mouseObjectOffSetX = event.mouseButton.x - unit_it->getGlobalBounds().left;
        mouseObjectOffSetY = event.mouseButton.y - unit_it->getGlobalBounds().top;
    }
}

void GameView::change_player_turn() {
    if (!(board_a_initialized || board_b_initialized)) {
        return;
    }
    if (end_turn_button.is_highlighted() && unit_moved_this_round == true) {
        if (current_player_turn == TURN::PLAYER_A) {
            current_player_turn = TURN::PLAYER_B;
            current_player = &playerB;
            other_player = &playerA;
        } else {
            current_player_turn = TURN::PLAYER_A;
            current_player = &playerA;
            other_player = &playerB;
        }
        unit_moved_this_round = false;
    }
}

void GameView::change_init_turn(sf::Event& event) {
    if (board_b_initialized && board_a_initialized) {
        return;
    }
    if (done_button.contains(event.mouseButton.x, event.mouseButton.y)) {
        if (current_player_turn == TURN::PLAYER_A) {
            if (playerA.get_board().get_state() == STATE::FULL) {
                board_a_initialized = true;
                current_player_turn = TURN::PLAYER_B;
                current_player = &playerB;
                other_player = &playerA;
                playerB.update_board(playerA.get_board());
            }
        } else {
            if (playerB.get_board().get_state() == STATE::FULL) {
                board_b_initialized = true;
                current_player_turn = TURN::PLAYER_A;
                current_player = &playerA;
                other_player = &playerB;
                playerA.update_board(playerB.get_board());
            }
        }
    }
}

void GameView::set_unit(sf::Event& event) {
    if (board_a_initialized && board_b_initialized) {
        return;
    }
    dragging = false;
    Board::Tile tile(return_tile(event.mouseButton.x, event.mouseButton.y));
    int idx = -1;
    if (current_player_turn == TURN::PLAYER_A) {
        idx = unit_it - &red_units_sprites[0];
    } else {
        idx = unit_it - &blue_units_sprites[0];
    }

    if (current_player->get_units_count(idx) < current_player->get_board().get_max_unit_count(idx)) {
        current_player->set_unit(tile.x, tile.y, idx);
    }
}

void GameView::set_active_unit(sf::Event& event) {
    if (is_out_of_the_board(event.mouseButton.x, event.mouseButton.y)) {
        active_unit.set_cords(-1, -1);
    }
    Board::Tile chosen_tile(return_tile(event.mouseButton.x, event.mouseButton.y));
    if (!current_player->get_board().get_unit(chosen_tile)) {
        return;
    }
    if (current_player->get_board().get_unit(chosen_tile)->get_owner() != current_player->get_player_number()) {
        return;
    }

    if (active_unit == chosen_tile && is_active_unit) {
        active_unit.set_cords(-1, -1);
        is_active_unit = false;
    } else {
        active_unit.set_cords(chosen_tile);
        is_active_unit = true;
    }
}

sf::Vector2f GameView::return_pixels(int col, int row) const {
    if (col < 0 && row < 0) {
        return sf::Vector2f{-1, -1};
    }
    return sf::Vector2f(TILE_SIZE * (col + 1), TILE_SIZE * (row + 1));
}

Board::Tile GameView::return_tile(const sf::Vector2f& coords) const {
    return Board::Tile((coords.x - TILE_SIZE) / TILE_SIZE, (coords.y - TILE_SIZE) / TILE_SIZE);
}

Board::Tile GameView::return_tile(int x, int y) const {
    if (x < 0 && y < 0) {
        return Board::Tile{-1, -1};
    }
    return return_tile(sf::Vector2f(x, y));
}

bool GameView::is_out_of_the_board(int x, int y) {
    if (current_player->get_tile_info(return_tile(x, y)) == "#") {
        return true;
    }
    return false;
}