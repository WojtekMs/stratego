#include "Box.hpp"

#include <iostream>
#include <sstream>

Box::Box(const std::string &text)
    : path_to_textures("images/board/"), max_char_count_inside_box(12),
      max_number_of_text_lines_inside_box(3), box_text_x_pos(-1.0f),
      box_text_y_pos(-1.0f), button_x_pos(-1.0f), button_y_pos(-1.0f) {
  			load_box_texture();
  load_font();
  set_default_text(text);
  update_max_char_count();
  set_button_text();
  box_sprite.setTexture(box_texture);
  update_button_pos();
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

void Box::set_default_text(const std::string &text) {
  box_text.setFont(font);
  box_text.setString(text);
  update_text_pos();
}

void Box::update_text_pos() {
  box_text_x_pos =
      (box_sprite.getPosition().x +
       (box_sprite.getGlobalBounds().width - box_text.getLocalBounds().width) /
           2);
  box_text_y_pos = static_cast<float>(box_sprite.getPosition().y +
                                      2 * box_text.getCharacterSize());
  box_text.setPosition(box_text_x_pos, box_text_y_pos);
}

void Box::update_button_pos() {
  button_x_pos = box_sprite.getPosition().x +
                 (box_sprite.getGlobalBounds().width - button.get_width()) / 2;
  button_y_pos = static_cast<float>(
      box_sprite.getPosition().y + box_sprite.getGlobalBounds().height -
      2 * box_text.getCharacterSize() - button.get_height());
  button.set_position(button_x_pos, button_y_pos);
}

void Box::set_position(int x, int y) {
  box_sprite.setPosition(x, y);
  update_text_pos();
  box_text.setPosition(box_text_x_pos, box_text_y_pos);
  update_button_pos();
  button.set_position(button_x_pos, button_y_pos);
}

void Box::set_position(const sf::Vector2f &coords) {
  set_position(coords.x, coords.y);
}

void Box::set_text(const std::string &text) {
  box_text.setString(text);
  break_text_into_lines();
  update_text_pos();
}

void Box::set_button_text(const std::string &text) { button.set_text(text); }

void Box::draw(sf::RenderWindow &win) {
  win.draw(box_sprite);
  win.draw(box_text);
  button.draw(win);
}

void Box::update_max_char_count() {
  int max_chars_per_line = static_cast<int>(box_sprite.getLocalBounds().width /
                                            box_text.getCharacterSize());
  max_char_count_inside_box =
      max_chars_per_line * max_number_of_text_lines_inside_box;
}

void Box::break_text_into_lines() {
  if (box_text.getString().getSize() * box_text.getCharacterSize() <
      box_sprite.getLocalBounds().width) {
    return;
  }
  std::istringstream temp_stream(box_text.getString());
  std::vector<std::string> words(
      (std::istream_iterator<std::string>(temp_stream)),
      std::istream_iterator<std::string>());
  std::string temp_text;
  size_t char_count_inside_line = 0;
  size_t line_count = 0;
  size_t space_count_in_line = 0;
  size_t char_count_that_will_fit_in_line = 0;
  size_t char_count_of_next_word = 0;
  size_t idx_of_the_first_char_in_new_line = 0;
  for (size_t i = 0; i < words.size() - 1; ++i) {
    char_count_of_next_word = words[i + 1].size();
    char_count_inside_line += words[i].size();
    if (char_count_inside_line * box_text.getCharacterSize() > get_width()) {
      temp_text += (words[i] + "\n");
      line_count++;
      idx_of_the_first_char_in_new_line = char_count_inside_line + 2;
      char_count_inside_line = 0;
    } else {
      char_count_that_will_fit_in_line =
          static_cast<std::size_t>(box_sprite.getLocalBounds().width) -
          char_count_inside_line * box_text.getCharacterSize();
      if (char_count_of_next_word > char_count_that_will_fit_in_line ||
          i == words.size() - 2) {
        float denting = (box_sprite.getLocalBounds().width -
                         char_count_inside_line * box_text.getCharacterSize()) /
                        2;
        int spaces =
            static_cast<int>(denting / box_text.getCharacterSize() + 0.5);
        temp_text.insert(idx_of_the_first_char_in_new_line, spaces, ' ');
      }
      temp_text += (words[i] + " ");
    }
    if (line_count > 3) {
      break;
    }
    if (i == words.size() - 2) {
      temp_text += words[i + 1];
    }
  }
  box_text.setString(temp_text);
}
