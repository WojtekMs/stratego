#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonInterface.hpp"

class Button : public ButtonInterface
{
protected:
    sf::Texture button_texture;
    sf::Texture highlighted_button_texture;

    void load_button_texture();
    void load_highlighted_button_texture();
public:
    explicit Button(const std::string& text = "default");
    void draw(sf::RenderWindow& win);
};



