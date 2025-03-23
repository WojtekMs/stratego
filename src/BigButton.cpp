#include "BigButton.hpp"

#include <iostream>

BigButton::BigButton(const std::string &text) : ButtonInterface(text) {
  load_button_texture();
  load_highlighted_button_texture();

  button.setTexture(button_texture);
  highlighted_button.setTexture(highlighted_button_texture);
}

void BigButton::load_button_texture() {
  if (!button_texture.loadFromFile(path_to_textures + "big_button.png")) {
    std::cerr << "big button texture failed to load!\n";
    abort();
  }
}

void BigButton::load_highlighted_button_texture() {
  if (!highlighted_button_texture.loadFromFile(path_to_textures +
                                               "big_button_highlighted.png")) {
    std::cerr << "big button highlighted texture failed to load!\n";
    abort();
  }
}

void BigButton::draw(sf::RenderWindow &win) {
  if (highlighted) {
    win.draw(highlighted_button);
  } else {
    win.draw(button);
  }
  win.draw(button_text);
}