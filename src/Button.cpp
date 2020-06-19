#include "Button.hpp"

#include <iostream>

Button::Button(const std::string& text)
:ButtonInterface(text)
{
    load_button_texture();
    load_highlighted_button_texture();
    button.setTexture(button_texture);
    highlighted_button.setTexture(highlighted_button_texture);
}

void Button::load_button_texture() {
    if (!button_texture.loadFromFile(path_to_textures + "button.png")) {
        std::cerr << "wooden texture loading inside Button class failed!\n";
        abort();
    }
}

void Button::load_highlighted_button_texture() {
    if (!highlighted_button_texture.loadFromFile(path_to_textures + "button_highlighted.png")) {
        std::cerr << "highlighted wooden texture loading inside Button class failed!\n";
        abort();
    }
}

void Button::draw(sf::RenderWindow& win) {
    if (highlighted) {
        win.draw(highlighted_button);
    } else {
        win.draw(button);
    }
    win.draw(button_text);
}
