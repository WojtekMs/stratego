#pragma once

#include "BigButton.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "cScreen.hpp"

class MainMenu : public cScreen {
  Player &playerA;
  Player &playerB;
  BigButton start_game_button;
  BigButton game_rules_button;
  BigButton exit_button;
  Button next;
  Button prev;
  Box player_1_name;
  Box player_2_name;
  bool names_entered;
  bool game_started_button_pressed;
  bool rules_button_pressed;
  bool exit_button_pressed;
  bool next_button_pressed;
  bool prev_button_pressed;
  bool player_1_name_approved;
  bool player_2_name_approved;
  bool entering_from_menu;
  std::string nickname;
  sf::String nickname_drawn;
  const std::string path_to_textures;
  int idx;

  std::array<sf::Texture, 5> rules_textures;
  sf::Texture logo_texture;
  std::array<sf::Sprite, 5> rules_sprites;
  sf::Sprite logo_sprite;

  void draw_menu(sf::RenderWindow &win);
  void draw_names(sf::RenderWindow &win);
  void draw_rules(sf::RenderWindow &win);
  void draw_rule(sf::RenderWindow &win, int idx);
  void highlight_buttons(int mouse_x, int mouse_y);
  void enter_names(sf::Event &event);
  void set_buttons_pressed();

public:
  MainMenu(Player &pA, Player &pB);
  std::string run(sf::RenderWindow &win) override;
};