#include "BigButton.hpp"

#include <iostream>

BigButton::BigButton(const std::string& text)
    {
        load_font();
        load_button_texture();
        load_highlighted_button_texture();
        set_default_button_text(text);
        update_text_pos();

    }

void BigButton::load_button_texture() {
    if (!button_texture.loadFromFile(path_to_textures + "big_button.png")) {
        std::cerr << "big button texture failed to load!\n";
        abort();
    }
}

void BigButton::load_highlighted_button_texture() {
    if (!highlighted_button_texture.loadFromFile(path_to_textures + "big_button_highlighted.png")) {
        std::cerr << "big button highlighted texture failed to load!\n";
        abort();
    }
}