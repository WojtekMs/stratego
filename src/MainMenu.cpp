#include "MainMenu.hpp"

MainMenu::MainMenu(Player& pA, Player& pB)
    : playerA(pA),
      playerB(pB),
      start_game_button("Start Game"),
      game_rules_button("Game Rules"),
      exit_button("Exit The Game"),
      next("Next"),
      prev("Previous"),
      names_entered(false),
      game_started_button_pressed(false),
      rules_button_pressed(false),
      exit_button_pressed(false),
      next_button_pressed(false),
      prev_button_pressed(false),
      player_1_name_approved(false),
      player_2_name_approved(false),
      entering_from_menu(true),
      path_to_textures("images/board/"),
      idx(0) {
    for (size_t i = 0; i < rules_textures.size(); ++i) {
        if (!rules_textures[i].loadFromFile(path_to_textures + "rules#" + std::to_string(i + 1) + ".png")) {
            std::cerr << "rules#" + std::to_string(i + 1) + " texture failed to load!\n";
            abort();
        }
        rules_sprites[i].setTexture(rules_textures[i]);
    }
    if (!logo_texture.loadFromFile(path_to_textures + "stratego_logo.png")) {
        std::cerr << "logo texture failed to load!\n";
        abort();
    }
    logo_sprite.setTexture(logo_texture);
}

std::string MainMenu::run(sf::RenderWindow& win) {
    while (true) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";  //will exit the application in the main function
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                set_buttons_pressed();
                if (names_entered && game_started_button_pressed) {
                    game_started_button_pressed = false;
                    return "game";
                }
                if (exit_button.is_highlighted() && exit_button_pressed) {
                    return "exit";
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                highlight_buttons(event.mouseMove.x, event.mouseMove.y);
            }
            enter_names(event);
        }
        win.clear();
        if (rules_button_pressed) {
            draw_rules(win);
        }
        if (!game_started_button_pressed && !rules_button_pressed) {
            draw_menu(win);
        }
        if (game_started_button_pressed) {
            draw_names(win);
        }

        win.display();
    }
}

void MainMenu::set_buttons_pressed() {
    if (start_game_button.is_highlighted() && !rules_button_pressed && !exit_button_pressed) {
        game_started_button_pressed = true;
    }
    if (player_1_name.button_is_highlighted() && !player_1_name_approved) {
        if (nickname.size() > 3) {
            playerA.set_name(nickname);
            nickname.clear();
            player_1_name_approved = true;
        }
    }
    if (player_2_name.button_is_highlighted() && !player_2_name_approved) {
        if (nickname.size() > 3) {
            playerB.set_name(nickname);
            nickname.clear();
            player_2_name_approved = true;
            names_entered = true;
        }
    }
    if (game_rules_button.is_highlighted() && !game_started_button_pressed && !exit_button_pressed) {
        rules_button_pressed = true;
    }
    if (rules_button_pressed) {
        if (next.is_highlighted()) {
            next_button_pressed = true;
        }
        if (prev.is_highlighted()) {
            prev_button_pressed = true;
        }
    }
    if (exit_button.is_highlighted() && !game_started_button_pressed && !rules_button_pressed) {
        exit_button_pressed = true;
    }
}

void MainMenu::draw_menu(sf::RenderWindow& win) {
    logo_sprite.setPosition((win.getSize().x - logo_sprite.getLocalBounds().width) / 2,
                                   0.8 * start_game_button.get_height());
    start_game_button.set_position((win.getSize().x - start_game_button.get_width()) / 2,
                                   (logo_sprite.getPosition().y + 1.5 * start_game_button.get_height()));
    game_rules_button.set_position(start_game_button.get_position().x,
                                   start_game_button.get_position().y + 1.25 * game_rules_button.get_height());
    exit_button.set_position(game_rules_button.get_position().x,
                             game_rules_button.get_position().y + 1.25 * exit_button.get_height());

    win.draw(logo_sprite);
    start_game_button.draw(win);
    game_rules_button.draw(win);
    exit_button.draw(win);
}

void MainMenu::draw_names(sf::RenderWindow& win) {
    if (!player_1_name_approved) {
        player_1_name.set_text("Red Player's Name: " + nickname);
        player_1_name.set_position((win.getSize().x - player_1_name.get_width()) / 2,
                                   (win.getSize().y - player_1_name.get_height()) / 2);
        player_1_name.draw(win);
    }
    if (player_1_name_approved && !player_2_name_approved) {
        player_2_name.set_text("Blue Player's Name: " + nickname);
        player_2_name.set_position(player_1_name.get_position());
        player_2_name.draw(win);
    }
}

void MainMenu::draw_rules(sf::RenderWindow& win) {
    if (entering_from_menu) {
        entering_from_menu = false;
        idx = 0;
        prev.set_text("Menu");
    }
    if (idx > 0) {
        prev.set_text("Previous");
    }
    if (idx == 0) {
        prev.set_text("Menu");
    }
    next.set_position(win.getSize().x - 1.25 * next.get_width(), win.getSize().y - 1.75 * next.get_height());
    prev.set_position(0.25 * next.get_width(), win.getSize().y - 1.75 * next.get_height());
    draw_rule(win, idx);
    if (next_button_pressed) {
        if (idx < 4) {
            idx++;
        }
        next_button_pressed = false;
    }
    if (prev_button_pressed && prev.get_text() != "Menu") {
        if (idx > 0) {
            idx--;
        } else if (idx == 0) {
            prev.set_text("Menu");
        }
        prev_button_pressed = false;
    }
    if (prev_button_pressed && prev.get_text() == "Menu") {
        prev_button_pressed = false;
        rules_button_pressed = false;
        game_started_button_pressed = false;
        entering_from_menu = true;
        return;
    }
    if (idx < 4) {
        next.draw(win);
    }
    prev.draw(win);
}

void MainMenu::draw_rule(sf::RenderWindow& win, int idx) {
    if (idx < 0) {
        return;
    }
    int rules_x_pos = (win.getSize().x - rules_sprites[idx].getLocalBounds().width) / 2;
    int rules_y_pos = (win.getSize().y - rules_sprites[idx].getLocalBounds().height) / 2;
    rules_sprites[idx].setPosition(rules_x_pos, rules_y_pos);
    win.draw(rules_sprites[idx]);
}

void MainMenu::highlight_buttons(int mouse_x, int mouse_y) {
    if (start_game_button.contains(mouse_x, mouse_y)) {
        start_game_button.highlight_on();
    } else {
        start_game_button.highlight_off();
    }
    if (game_rules_button.contains(mouse_x, mouse_y)) {
        game_rules_button.highlight_on();
    } else {
        game_rules_button.highlight_off();
    }
    if (exit_button.contains(mouse_x, mouse_y)) {
        exit_button.highlight_on();
    } else {
        exit_button.highlight_off();
    }
    if (player_1_name.button_contains(mouse_x, mouse_y) && game_started_button_pressed) {
        player_1_name.set_button_highlight_on();
    } else {
        player_1_name.set_button_highlight_off();
    }
    if (player_2_name.button_contains(mouse_x, mouse_y) && player_1_name_approved) {
        player_2_name.set_button_highlight_on();
    } else {
        player_2_name.set_button_highlight_off();
    }
    if (next.contains(mouse_x, mouse_y)) {
        next.highlight_on();
    } else {
        next.highlight_off();
    }
    if (prev.contains(mouse_x, mouse_y)) {
        prev.highlight_on();
    } else {
        prev.highlight_off();
    }
}

void MainMenu::enter_names(sf::Event& event) {
    if (!game_started_button_pressed) {
        return;
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode > 31 && event.text.unicode < 128 && nickname.size() < 21) {
            nickname += event.text.unicode;
        }
        if (event.text.unicode == '\b' && !nickname.empty()) {
            nickname.pop_back();
        }
    }
}
