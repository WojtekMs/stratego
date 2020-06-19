#pragma once

#include <SFML/Graphics.hpp>

class Button
{
protected:
    int text_x_pos;
    int text_y_pos;
    bool highlighted;
    // sf::RectangleShape button_box;
    sf::Texture button_texture;
    sf::Texture highlighted_button_texture;
    sf::Sprite button;
    sf::Sprite highlighted_button;
    sf::Font font;
    sf::Text button_text;

    void update_text_pos();
public:
    // Button(const sf::Vector2f& size, const std::string& text);
    Button(const std::string& text);
    void set_text(const std::string& text);
    void set_position(int x, int y);
    void set_position(sf::Vector2f coords);
    void draw(sf::RenderWindow& win);
    float get_height() { return button.getGlobalBounds().height; };
    float get_width() { return button.getGlobalBounds().width; };
    bool contains(int x, int y) { return button.getGlobalBounds().contains(x, y); };
    void highlight_on() { highlighted = true; };
    void highlight_off() { highlighted = false; };
    bool is_highlighted() const { return highlighted; };
    sf::Vector2f get_position() const { return button.getPosition(); };
};



