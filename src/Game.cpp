#include "Game.hpp"

Game::Game(GameView& g_view, GameController& g_controller)
    : game_view(g_view),
      game_controller(g_controller),
      clock_started(false) {
}

std::string Game::run(sf::RenderWindow& win) {
    

    while (win.isOpen()) {
        sf::Event event;
        game_view.update_players(game_controller.get_current_player(), game_controller.get_other_player());
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return "menu";
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(game_controller.get_end_game_info_box_button_pressed()) {
                    return "menu";
                }
            }
            game_controller.handle_events(event);
        }
        win.clear();
        draw(win);
        win.display();
    }
}

void Game::draw(sf::RenderWindow& win) {
    if (game_controller.get_game_finished()) {
        game_view.draw_end_game_screen(win, game_controller.get_victorious_player_name());
        return;
    }
    game_view.draw_board_border(win);
    game_view.draw_grass(win);
    game_view.draw_obstacles(win);
    if (game_controller.get_end_turn_button_pressed()) {
        game_view.draw_info_box(win);
        return;
    }
    game_controller.update_unit_attacked(clock.restart());
    if (game_controller.get_unit_attacked()) {
        game_view.draw_attack_info_box(win, game_controller.get_attacker(), game_controller.get_attacked());
        return;
    }
    game_view.draw_units(win);
    if (game_controller.get_is_active_unit()) {
        game_view.draw_unit_highlight(win, game_controller.get_active_unit());
    }
    if (!game_controller.both_boards_set()) {
        game_view.draw_units_for_init(win, game_controller.get_dragging(), 
        game_controller.get_selected_init_unit_idx(), game_controller.get_mouse_data());
        game_view.draw_done_button(win);
        game_view.draw_randomize_button(win);
        if (game_controller.get_is_active_unit()) {
            game_view.draw_remove_button(win);
        }
    } else {
        game_view.draw_end_turn_button(win);
        if (game_controller.get_is_active_unit() && !game_controller.get_unit_moved_this_round()) {
            game_view.draw_possible_moves_for_active_unit(win, game_controller.get_active_unit());
        }
    }
}
