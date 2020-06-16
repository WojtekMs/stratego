#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    int text_x_pos;
    int text_y_pos;
    bool highlighted;
    // sf::RectangleShape button_box;
    sf::Texture wooden;
    sf::Texture highlighted_wooden;
    sf::Sprite button_box;
    sf::Sprite highlighted_button;
    sf::Font font;
    sf::Text button_text;

    void update_text_pos();
public:
    // Button(const sf::Vector2f& size, const std::string& text);
    Button(const std::string& text);
    void set_text(const std::string& text);
    void set_position(int x, int y);
    void draw(sf::RenderWindow& win);
    float get_height() { return button_box.getGlobalBounds().height; };
    float get_width() { return button_box.getGlobalBounds().width; };
    bool contains(int x, int y) { return button_box.getGlobalBounds().contains(x, y); };
    void highlight_on() { highlighted = true; };
    void highlight_off() { highlighted = false; };
};



