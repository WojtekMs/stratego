#include "GameController.hpp"

#include <algorithm>

#include "GameView.hpp"
#include "Player.hpp"

GameController::GameController(Player& pA, Player& pB, GameView& g_view)
    : playerA(pA),
      playerB(pB),
      game_view(g_view),
      current_player(&pA),
      other_player(&pB),
      attacker{},
      attacked{},
      victorious_player_name("none"),
      current_player_turn(TURN::PLAYER_A),
      TILE_SIZE(64),
      selected_unit_idx(0),
      dragging(false),
      board_a_initialized(false),
      board_b_initialized(false),
      is_active_unit(false),
      unit_moved_this_round(false),
      end_turn_button_pressed(false),
      turn_approved(false),
      unit_attacked(false),
      remove_button_pressed(false),
      done_button_pressed(false),
      end_game_info_box_button_pressed(false),
      game_finished(false),
      active_unit(-1, -1),
      attacking_unit(-1, -1),
      attacked_unit(-1, -1) {
}

void GameController::update_unit_attacked(const sf::Time& time_past) {
    if (unit_attacked) {
        total_time_unit_attacked += time_past;
    }
    if (total_time_unit_attacked.asSeconds() > 1.5) {
        total_time_unit_attacked = sf::Time();
        unit_attacked = false;
    }
}

void GameController::drag_red_player(sf::Event& event) {
    const sf::Sprite* unit_selected = std::find_if(game_view.get_red_units_sprites().begin(), game_view.get_red_units_sprites().end(),
                                                   [&event](const sf::Sprite& unit_sprite) {
                                                       return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                                                   });
    if (unit_selected != game_view.get_red_units_sprites().end()) {
        dragging = true;
        m_data.mouse_object_offset_x = event.mouseButton.x - unit_selected->getGlobalBounds().left;
        m_data.mouse_object_offset_y = event.mouseButton.y - unit_selected->getGlobalBounds().top;
    }
    selected_unit_idx = unit_selected - &game_view.get_red_units_sprites()[0];
}

void GameController::drag_blue_player(sf::Event& event) {
    const sf::Sprite* unit_selected = std::find_if(game_view.get_blue_units_sprites().begin(), game_view.get_blue_units_sprites().end(),
                                                   [&event](const sf::Sprite& unit_sprite) {
                                                       return unit_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                                                   });
    if (unit_selected != game_view.get_blue_units_sprites().end()) {
        dragging = true;
        m_data.mouse_object_offset_x = event.mouseButton.x - unit_selected->getGlobalBounds().left;
        m_data.mouse_object_offset_y = event.mouseButton.y - unit_selected->getGlobalBounds().top;
    }
    selected_unit_idx = unit_selected - &game_view.get_blue_units_sprites()[0];
}

void GameController::change_player_turn() {
    if (unit_moved_this_round && turn_approved) {
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
        turn_approved = false;
        is_active_unit = false;
    }
}

void GameController::change_init_turn(sf::Event& event) {
    if (done_button_pressed) {
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
        is_active_unit = false;
        done_button_pressed = false;
    }
}

void GameController::set_unit(sf::Event& event) {
    dragging = false;
    Board::Tile tile(return_tile(event.mouseButton.x, event.mouseButton.y));
    if (current_player->get_units_count(selected_unit_idx) < current_player->get_board().get_max_unit_count(selected_unit_idx)) {
        current_player->set_unit(tile.x, tile.y, selected_unit_idx);
    }
}

void GameController::set_active_unit(sf::Event& event) {
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

void GameController::set_button_highlights(int mouse_x, int mouse_y) {
    if (game_view.get_done_button().contains(mouse_x, mouse_y)) {
        game_view.done_button.highlight_on();
    } else {
        game_view.done_button.highlight_off();
    }
    if (game_view.get_remove_button().contains(mouse_x, mouse_y)) {
        game_view.remove_button.highlight_on();
    } else {
        game_view.remove_button.highlight_off();
    }
    if (game_view.get_end_turn_button().contains(mouse_x, mouse_y)) {
        game_view.end_turn_button.highlight_on();
    } else {
        game_view.end_turn_button.highlight_off();
    }
    if (game_view.get_info_box().button_contains(mouse_x, mouse_y) && end_turn_button_pressed) {
        game_view.info_box.set_button_highlight_on();
    } else {
        game_view.info_box.set_button_highlight_off();
    }
    if (game_view.get_end_game_info_box().button_contains(mouse_x, mouse_y)) {
        game_view.end_game_info_box.set_button_highlight_on();
    } else {
        game_view.end_game_info_box.set_button_highlight_off();
    }
}

void GameController::remove_unit() {
    if (is_active_unit && remove_button_pressed) {
        current_player->remove_unit(active_unit.x, active_unit.y);
        active_unit.set_cords(-1, -1);
        is_active_unit = false;
        remove_button_pressed = false;
    }
}

void GameController::resolve_unit_conflict(const Board::Tile& attacked_unit) {
    switch (current_player->attack(active_unit, attacked_unit)) {
    case RESULT::WON:
        current_player->remove_unit(attacked_unit);
        other_player->reverse_remove_unit(attacked_unit);
        break;
    case RESULT::DRAW:
        current_player->remove_unit(active_unit);
        current_player->remove_unit(attacked_unit);
        other_player->reverse_remove_unit(active_unit);
        other_player->reverse_remove_unit(attacked_unit);
        active_unit.set_cords(-1, -1);
        break;
    case RESULT::LOST:
        current_player->remove_unit(active_unit);
        other_player->reverse_remove_unit(active_unit);
        active_unit.set_cords(-1, -1);
        break;
    }
    is_active_unit = false;
}

void GameController::move_active_unit(sf::Event& event) {
    Board::Tile chosen_tile(return_tile(event.mouseButton.x, event.mouseButton.y));
    if (!is_active_unit) {
        return;
    }
    if (unit_moved_this_round) {
        return;
    }
    if (!current_player->can_move(active_unit, chosen_tile)) {
        return;
    }
    if (current_player->get_tile_info(chosen_tile) == "enemy") {
        if (current_player->get_board().get_unit(chosen_tile)->get_type() == "flag") {
            game_finished = true;
            victorious_player_name = current_player->get_player_name();
        }
        attacker = current_player->get_board().get_unit(active_unit);
        attacked = current_player->get_board().get_unit(chosen_tile);
        resolve_unit_conflict(chosen_tile);
        unit_attacked = true;
        unit_moved_this_round = true;

    }
    if (current_player->move_unit(active_unit, chosen_tile)) {
        other_player->reverse_move_unit(active_unit, chosen_tile);
        active_unit.set_cords(-1, -1);
        unit_moved_this_round = true;
        is_active_unit = false;
    }
}

void GameController::TEST_SET_RANDOM_UNITS() {
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

void GameController::set_buttons_pressed() {
    if (game_view.get_end_turn_button().is_highlighted() && unit_moved_this_round) {
        end_turn_button_pressed = true;
    }
    if (game_view.get_info_box().button_is_highlighted()) {
        turn_approved = true;
        end_turn_button_pressed = false;
    }
    if (!(board_a_initialized && board_b_initialized) && game_view.get_remove_button().is_highlighted()) {
        remove_button_pressed = true;
    }
    if (!(board_a_initialized && board_b_initialized) && game_view.get_done_button().is_highlighted()) {
        done_button_pressed = true;
    }
    if (game_finished && game_view.get_end_game_info_box().button_is_highlighted()) {
        end_game_info_box_button_pressed = true;
    }
}

void GameController::handle_events(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        set_buttons_pressed();
        if (!(board_a_initialized && board_b_initialized)) {
            if (current_player_turn == TURN::PLAYER_A) {
                drag_red_player(event);
            } else {
                drag_blue_player(event);
            }
            remove_unit();
            change_init_turn(event);
        }
        if (!is_out_of_the_board(event.mouseButton.x, event.mouseButton.y)) {
            set_active_unit(event);
        }
        if (board_a_initialized && board_b_initialized) {
            change_player_turn();
            move_active_unit(event);
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (!(board_a_initialized && board_b_initialized)) {
            set_unit(event);
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        m_data.mouse_x = event.mouseMove.x;
        m_data.mouse_y = event.mouseMove.y;
        set_button_highlights(m_data.mouse_x, m_data.mouse_y);
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            TEST_SET_RANDOM_UNITS();
        }
    }
}

sf::Vector2f GameController::return_pixels(int col, int row) const {
    if (col < 0 && row < 0) {
        return sf::Vector2f{-1, -1};
    }
    return sf::Vector2f(TILE_SIZE * (col + 1), TILE_SIZE * (row + 1));
}

Board::Tile GameController::return_tile(const sf::Vector2f& coords) const {
    return Board::Tile((coords.x - TILE_SIZE) / TILE_SIZE, (coords.y - TILE_SIZE) / TILE_SIZE);
}

Board::Tile GameController::return_tile(int x, int y) const {
    if (x < 0 && y < 0) {
        return Board::Tile{-1, -1};
    }
    return return_tile(sf::Vector2f(x, y));
}

bool GameController::is_out_of_the_board(int x, int y) {
    if (current_player->get_tile_info(return_tile(x, y)) == "#") {
        return true;
    }
    return false;
}

bool GameController::both_boards_set() const {
    if (board_a_initialized && board_b_initialized) {
        return true;
    }
    return false;
};