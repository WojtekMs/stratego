#pragma once

#include <string>

#include "Button.hpp"

class Box
{
    protected:
    const std::string path_to_textures;
    int text_x_pos;
    int text_y_pos;
    Button button;
    sf::Font font;
    sf::Text box_text;
    sf::Texture box_texture;
    sf::Sprite box_sprite;

    void load_box_texture();
    void load_font();
    void set_default_text(const std::string& text);
    void update_text_pos();
    public:
    explicit Box(const std::string& text = "default");
    void set_position(int x, int y);
    void set_position(const sf::Vector2f& coords);
    void set_text(const std::string& text);
    void set_button_text(const std::string& text);
    void set_button_highlight_on() { button.highlight_on(); };
    void set_button_highlight_off() { button.highlight_off(); };
    bool button_contains(int x, int y) const { return button.contains(x, y); };
    bool button_is_highlighted() const { return button.is_highlighted(); };
    void draw(sf::RenderWindow& win);
    float get_height() const { return box_sprite.getGlobalBounds().height; };
    float get_width() const { return box_sprite.getGlobalBounds().width; };
    sf::Vector2f get_position() const { return box_sprite.getPosition(); };


};