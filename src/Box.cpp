#include "Box.hpp"

#include <iostream>

Box::Box(const std::string& text)
    : path_to_textures("images/board/"),
    text_x_pos(-1),
    text_y_pos(-1) {
    load_box_texture();
    load_font();
    box_sprite.setTexture(box_texture);
    set_default_text(text);
    update_text_pos();
    
}

void Box::load_box_texture() {
    if (!box_texture.loadFromFile(path_to_textures + "box.png")) {
        std::cerr << "box texture failed to load!\n";
        abort();
    }
}

void Box::load_font() {
    if (!font.loadFromFile("font/chandas1-2.ttf")) {
        std::cerr << "font failed to load inside Box class!\n";
        abort();
    }
}

void Box::set_default_text(const std::string& text) {
    box_text.setFont(font);
    box_text.setString(text);
    update_text_pos();
}

void Box::update_text_pos() {
    text_x_pos = (box_sprite.getPosition().x + (box_sprite.getGlobalBounds().width - box_text.getLocalBounds().width) / 2);
    text_y_pos = (box_sprite.getPosition().y + (box_sprite.getGlobalBounds().height - box_text.getCharacterSize()) / 2);
    box_text.setPosition(text_x_pos, text_y_pos);
}

void Box::set_position(int x, int y) {
    box_sprite.setPosition(x, y);
    box_text.setPosition(x, y);
    button.set_position(x, y);
}

void Box::set_position(const sf::Vector2f& coords) {
    set_position(coords.x, coords.y);
}

void Box::set_text(const std::string& text) {
    box_text.setString(text);
    update_text_pos();
}

void Box::set_button_text(const std::string& text) {
    button.set_text(text);
}

void Box::draw(sf::RenderWindow& win) {
    win.draw(box_sprite);
    win.draw(box_text);
    button.draw(win);
}
