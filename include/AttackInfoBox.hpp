#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Unit.hpp"

class AttackInfoBox
{
    const std::string path_to_textures;
    int attacking_unit_pos_x;
    int attacking_unit_pos_y;
    int attacked_unit_pos_x;
    int attacked_unit_pos_y;
    std::array<sf::Sprite*, 12> red_units_sprites_ptrs;
    std::array<sf::Sprite*, 12> blue_units_sprites_ptrs;
    sf::Texture box_texture;
    sf::Sprite box_sprite;
    sf::Font box_font;
    sf::Text box_text;
    sf::Sprite attacking_unit;
    sf::Sprite attacked_unit;
    // std::shared_ptr<Unit> attacking_unit;
    // std::shared_ptr<Unit> attacked_unit;

    int get_unit_sprite_idx(const std::shared_ptr<Unit>& unit);
    void load_box_texture();
    void load_font();
    void update_attacking_unit_pos();
    void update_attacked_unit_pos();
    void update_box_text_pos();
    public:
    AttackInfoBox(std::array<sf::Sprite, 12>& red_units_sprites, std::array<sf::Sprite, 12>& blue_units_sprites);
    void draw(sf::RenderWindow& win);
    void set_position(int x, int y);
    void set_attacking_unit(const std::shared_ptr<Unit>& attacker);
    void set_attacked_unit(const std::shared_ptr<Unit>& victim);
    float get_height() const { return box_sprite.getGlobalBounds().height; };
    float get_width() const { return box_sprite.getGlobalBounds().width; };
    
    
};