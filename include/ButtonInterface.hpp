#pragma once

#include <SFML/Graphics.hpp>

class ButtonInterface {
protected:
    int text_x_pos;
    int text_y_pos;
    bool highlighted;
    const std::string path_to_textures;
    sf::Sprite button;
    sf::Sprite highlighted_button;
    sf::Font font;
    sf::Text button_text;

    void load_font();
    void set_default_button_text(const std::string& text);
    void update_text_pos();

public:
    explicit ButtonInterface(const std::string& text);
    void set_text(const std::string& text);
    void set_position(int x, int y);
    void set_position(sf::Vector2f coords);
    virtual void draw(sf::RenderWindow& win) = 0;
    float get_height() const { return button.getGlobalBounds().height; };
    float get_width() const { return button.getGlobalBounds().width; };
    bool contains(int x, int y) const { return button.getGlobalBounds().contains(x, y); };
    void highlight_on() { highlighted = true; };
    void highlight_off() { highlighted = false; };
    bool is_highlighted() const { return highlighted; };
    sf::Vector2f get_position() const { return button.getPosition(); };
};