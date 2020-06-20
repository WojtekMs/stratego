#include "GameView.hpp"

#include <algorithm>

#include "Player.hpp"

GameView::GameView(Player& pA, Player& pB)
    : playerA(pA),
      playerB(pB),
      current_player(&playerA),
      other_player(&playerB),
      current_player_turn(TURN::PLAYER_A),
      board_textures_path("images/board/"),
      pieces_textures_path("images/pieces/"),
      TILE_SIZE(64),
      X_ADDITIONAL_SPACE(512),
      window_size(12 * TILE_SIZE + X_ADDITIONAL_SPACE, 14 * TILE_SIZE),
      sprite_initial_position(-1, -1),
      clock_started(false),
      done_button("Done"),
      remove_button("Remove"),
      end_turn_button("End Turn"),
      info_box("End of Turn"),
      attack_info_box(red_units_sprites, blue_units_sprites),
      end_game_info_box("None")
{
    load_obstacle_textures();
    load_grass_textures();
    load_board_border_texture();
    load_red_units_textures();
    load_blue_units_textures();
    load_highlight_textures();

    set_obstacle_sprites();
    set_red_units_sprites();
    set_blue_units_sprites();
    set_highlight_sprites();

    load_font();
    text.setFont(font);

    board_border.setTexture(board_border_texture);
    grass_light.setTexture(grass_light_texture);
    grass_dark.setTexture(grass_dark_texture);
}

void GameView::set_obstacle_sprites() {
    for (size_t i = 0; i < obstacle_sprites.size(); i++) {
        obstacle_sprites[i].setTexture(obstacle_textures[i]);
    }
}

void GameView::load_board_border_texture() {
    if (!board_border_texture.loadFromFile("images/board/border_scaled.png")) {
        std::cerr << "board border error loading from file!\n";
        abort();
    }
}

void GameView::load_grass_textures() {
    if (!grass_light_texture.loadFromFile("images/board/grass1_scaled.png")) {
        std::cerr << "grass light error loading from file!\n";
        abort();
    }
    if (!grass_dark_texture.loadFromFile("images/board/grass2_scaled.png")) {
        std::cerr << "grass dark error loading from file!\n";
        abort();
    }
}

void GameView::load_obstacle_textures() {
    for (size_t i = 0; i < obstacle_textures.size(); ++i) {
        if (i <= 3) {
            if (!obstacle_textures[i].loadFromFile(board_textures_path + "lake1_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "obstacle texture lake1_" + std::to_string(i + 1) + "failed to load!\n";
                abort();
            }
        } else {
            if (!obstacle_textures[i].loadFromFile(board_textures_path + "lake2_" + std::to_string(i - 3) + ".png")) {
                std::cerr << "obstacle texture lake2_" + std::to_string(i + 1) + "failed to load!\n";
                abort();
            }
        }
    }
}

void GameView::load_font() {
    if (!font.loadFromFile("font/chandas1-2.ttf")) {
        std::cerr << "font loading failed!\n";
        abort();
    }
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
    for (size_t i = 0; i < 9; ++i) {
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

void GameView::update_players(Player* current, Player* other) {
    current_player = current;
    other_player = other;
    current_player_turn = current_player->get_player_number();
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
            obstacle_sprites[i].setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[i]);
            i++;
        }
        for (size_t col = 6; col < 8; ++col) {
            size_t obstacle_x_pos = TILE_SIZE * (col + 1);
            obstacle_sprites[j].setPosition(obstacle_x_pos, obstacle_y_pos);
            win.draw(obstacle_sprites[j]);
            j++;
        }
    }
}

void GameView::draw_units_for_init(sf::RenderWindow& win, bool is_dragging, int selected_units_idx, const mouse_data& m_data) {
    if (current_player_turn == TURN::PLAYER_A) {
        draw_red_init_units(win, is_dragging, selected_units_idx, m_data);
    } else {
        draw_blue_init_units(win, is_dragging, selected_units_idx, m_data);
    }
    draw_done_button(win);
}

void GameView::draw_red_init_units(sf::RenderWindow& win, bool is_dragging, int selected_unit_idx, const mouse_data& m_data) {
    const int x_denting = board_border.getGlobalBounds().width;
    const int y_denting = TILE_SIZE;
    int col_count = 0;
    int row_count = 0;
    for (size_t i = 0; i < red_units_sprites.size(); ++i) {
        if (i != 0 && i % 4 == 0) {
            col_count = 0;
            row_count++;
        }
        red_units_sprites[i].setPosition(x_denting + 2 * col_count * TILE_SIZE, y_denting + row_count * TILE_SIZE);
        text.setPosition(x_denting + TILE_SIZE + 2 * col_count * TILE_SIZE, y_denting + TILE_SIZE / 4 + row_count * TILE_SIZE);
        text.setString("x" + std::to_string(playerA.get_board().get_max_unit_count(i) - playerA.get_units_count(i)));
        if (is_dragging == true) {
            red_units_sprites[selected_unit_idx].setPosition(m_data.mouse_x - m_data.mouse_object_offset_x, m_data.mouse_y - m_data.mouse_object_offset_y);
        }
        win.draw(red_units_sprites[i]);
        win.draw(text);
        col_count++;
    }
}

void GameView::draw_blue_init_units(sf::RenderWindow& win, bool is_dragging, int selected_unit_idx, const mouse_data& m_data) {
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
        if (is_dragging == true) {
            blue_units_sprites[selected_unit_idx].setPosition(m_data.mouse_x - m_data.mouse_object_offset_x, m_data.mouse_y - m_data.mouse_object_offset_y);
        }
        win.draw(blue_units_sprites[i]);
        win.draw(text);
        col_count++;
    }
}

void GameView::draw_done_button(sf::RenderWindow& win) {
    const int x_denting = board_border.getGlobalBounds().width;
    done_button.set_position(x_denting + (X_ADDITIONAL_SPACE - done_button.get_width()) / 2, TILE_SIZE * 6);
    done_button.draw(win);
}

void GameView::draw_remove_button(sf::RenderWindow& win) {
    remove_button.set_position(done_button.get_position().x, done_button.get_position().y + done_button.get_height() + TILE_SIZE);
    remove_button.draw(win);
}

void GameView::draw_end_turn_button(sf::RenderWindow& win) {
    end_turn_button.set_position(done_button.get_position());
    end_turn_button.draw(win);
}

void GameView::draw_info_box(sf::RenderWindow& win) {
    info_box.set_text(other_player->get_player_name() + "'s turn!");
    info_box.set_position((win.getSize().x - info_box.get_width()) / 2, (win.getSize().y - info_box.get_height()) / 2);
    info_box.draw(win);
}

void GameView::draw_attack_info_box(sf::RenderWindow& win, const std::shared_ptr<Unit>& attacker, const std::shared_ptr<Unit>& attacked) {
    if (!clock_started) {
        clock.restart();
        clock_started = true;
    }
    sf::Time time_past = clock.getElapsedTime();
    attack_info_box.set_position((window_size.x - attack_info_box.get_width()) / 2, (window_size.y - attack_info_box.get_height()) / 2);
    attack_info_box.set_attacking_unit(attacker);
    attack_info_box.set_attacked_unit(attacked);
    attack_info_box.draw(win);
    if (time_past.asSeconds() > 1.5) {
        clock_started = false;
    }
}

void GameView::draw_units(sf::RenderWindow& win) {
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
        }
    }
}

void GameView::draw_unit_highlight(sf::RenderWindow& win, const Board::Tile& active_unit) {
    yellow_highlight_sprite.setPosition(return_pixels(active_unit.x, active_unit.y));
    win.draw(yellow_highlight_sprite);
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

void GameView::draw_possible_moves_for_active_unit(sf::RenderWindow& win, const Board::Tile& active_unit) {
    if (!current_player->get_board().get_unit(active_unit.x, active_unit.y)) {
        return;
    }
    if (current_player->get_board().get_unit(active_unit.x, active_unit.y)->get_type() == "scout") {
        highlight_scout_moves(win, active_unit);
    } else {
        highlight_regular_moves(win, active_unit);
    }
}

void GameView::highlight_regular_moves(sf::RenderWindow& win, const Board::Tile& active_unit) {
    highlight_tile(win, active_unit, active_unit.x - 1, active_unit.y);
    highlight_tile(win, active_unit, active_unit.x + 1, active_unit.y);
    highlight_tile(win, active_unit, active_unit.x, active_unit.y + 1);
    highlight_tile(win, active_unit, active_unit.x, active_unit.y - 1);
}

void GameView::highlight_scout_moves(sf::RenderWindow& win, const Board::Tile& active_unit) {
    for (int col = active_unit.x + 1; col < current_player->get_board().get_width(); ++col) {
        if (!highlight_tile(win, active_unit, col, active_unit.y)) {
            break;
        }
    }
    for (int col = active_unit.x - 1; col >= 0; --col) {
        if (!highlight_tile(win, active_unit, col, active_unit.y)) {
            break;
        }
    }
    for (int row = active_unit.y + 1; row < current_player->get_board().get_height(); ++row) {
        if (!highlight_tile(win, active_unit, active_unit.x, row)) {
            break;
        }
    }
    for (int row = active_unit.y - 1; row >= 0; --row) {
        if (!highlight_tile(win, active_unit, active_unit.x, row)) {
            break;
        }
    }
}

bool GameView::highlight_tile(sf::RenderWindow& win, const Board::Tile& active_unit, int to_x, int to_y) {
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

void GameView::draw_end_game_screen(sf::RenderWindow& win, const std::string& victorious_name) {
    end_game_info_box.set_text("Congratulations " + victorious_name + " you won!\n");
    end_game_info_box.set_position(info_box.get_position());
    end_game_info_box.draw(win);
}

void GameView::draw_board_border(sf::RenderWindow& win) {
    win.draw(board_border);
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