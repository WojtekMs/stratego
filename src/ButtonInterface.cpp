#include "ButtonInterface.hpp"

#include <iostream>

ButtonInterface::ButtonInterface(const std::string &text)
    : path_to_textures("images/board/") {
  load_font();
  set_default_button_text(text);
  update_text_pos();
  highlighted = false;
}

void ButtonInterface::load_font() {
  if (!font.loadFromFile("font/chandas1-2.ttf")) {
    std::cerr << "font failed loading inside ButtonInterface class!\n";
    abort();
  }
}

void ButtonInterface::set_default_button_text(const std::string &text) {
  button_text.setFont(font);
  button_text.setString(text);
  button_text.setFillColor(sf::Color::Yellow);
}

void ButtonInterface::update_text_pos() {
  text_x_pos = (button.getPosition().x + (button.getGlobalBounds().width -
                                          button_text.getLocalBounds().width) /
                                             2);
  text_y_pos =
      (button.getPosition().y +
       (button.getGlobalBounds().height - button_text.getCharacterSize()) / 2);
  button_text.setPosition(text_x_pos, text_y_pos);
}

void ButtonInterface::set_position(int x, int y) {
  button.setPosition(x, y);
  highlighted_button.setPosition(x, y);
  update_text_pos();
}

void ButtonInterface::set_position(sf::Vector2f coords) {
  set_position(coords.x, coords.y);
}

void ButtonInterface::set_text(const std::string &text) {
  button_text.setString(text);
  update_text_pos();
}