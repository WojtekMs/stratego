#pragma once

#include "ButtonInterface.hpp"

class BigButton : public ButtonInterface {
protected:
  sf::Texture button_texture;
  sf::Texture highlighted_button_texture;

  void load_button_texture();
  void load_highlighted_button_texture();

public:
  explicit BigButton(const std::string &button_text = "default");
  void draw(sf::RenderWindow &win);
};