#include "Button.hpp"

#include <iostream>

Button::Button(const std::string& text)
{
    if(!font.loadFromFile("font/chandas1-2.ttf")) {
        std::cerr << "font failed loading inside Button class!\n";
        abort();
    }
    if (!wooden.loadFromFile("images/board/button.png")) {
        std::cerr << "wooden texture loading inside Button class failed!\n";
        abort();
    }
    if (!highlighted_wooden.loadFromFile("images/board/button_highlighted.png")) {
        std::cerr << "highlighted wooden texture loading inside Button class failed!\n";
        abort();
    }
    button_text.setFont(font);
    button_text.setString(text);
    button_text.setFillColor(sf::Color::Yellow);
    update_text_pos();
    button_box.setTexture(wooden);
    highlighted_button.setTexture(highlighted_wooden);
    highlighted = false;
    // button_box.setOutlineColor(sf::Color::Red);
    // button_box.setOutlineThickness(3);
    // button_box.setFillColor(sf::Color(150, 75, 0, 130));
}

void Button::update_text_pos() {
    text_x_pos = (button_box.getPosition().x + (button_box.getGlobalBounds().width - button_text.getLocalBounds().width) / 2);
    text_y_pos = (button_box.getPosition().y + (button_box.getGlobalBounds().height - button_text.getCharacterSize()) / 2);
    button_text.setPosition(text_x_pos, text_y_pos);

}

void Button::set_position(int x, int y) {
    button_box.setPosition(x, y);
    highlighted_button.setPosition(x, y);
    update_text_pos();
}

void Button::set_position(sf::Vector2f coords) {
    set_position(coords.x, coords.y);
}

void Button::set_text(const std::string& text) {
    button_text.setString(text);
    update_text_pos();
}

void Button::draw(sf::RenderWindow& win) {
    if (highlighted) {
        win.draw(highlighted_button);
    } else {
        win.draw(button_box);
    }
    win.draw(button_text);
}
