#include "AttackInfoBox.hpp"

#include <iostream>

#include "Board.hpp"
#include "unit/visit/Attack.hpp"
#include "unit/visit/GetOwner.hpp"
#include "unit/visit/GetUnitSpriteId.hpp"

AttackInfoBox::AttackInfoBox(std::array<sf::Sprite, 12> &red_units_sprites,
                             std::array<sf::Sprite, 12> &blue_units_sprites,
                             sf::Sprite &winning_unit_highlight)
    : path_to_textures("images/board/"), attacking_unit_pos_x(-1),
      attacking_unit_pos_y(-1), attacked_unit_pos_x(-1),
      attacked_unit_pos_y(-1), attacking_unit{}, attacked_unit{},
      attacker_ptr{}, attacked_ptr{}, winner_highlight(winning_unit_highlight) {
  for (int i = 0; i < red_units_sprites_ptrs.size(); ++i) {
    red_units_sprites_ptrs[i] = &red_units_sprites[i];
  }
  for (int i = 0; i < blue_units_sprites_ptrs.size(); ++i) {
    blue_units_sprites_ptrs[i] = &blue_units_sprites[i];
  }
  load_box_texture();
  load_font();
  box_text.setFont(box_font);
  box_text.setString("VS");
  box_text.setFillColor(sf::Color::Yellow);
  box_text.setCharacterSize(40);
  box_sprite.setTexture(box_texture);
}

void AttackInfoBox::draw(sf::RenderWindow &win) {
  update_attacked_unit_pos();
  update_attacking_unit_pos();
  update_box_text_pos();
  set_winner_highlight();
  win.draw(box_sprite);
  win.draw(attacking_unit);
  win.draw(box_text);
  win.draw(attacked_unit);
  draw_winner_highlight(win);
}

void AttackInfoBox::load_box_texture() {
  if (!box_texture.loadFromFile(path_to_textures + "attack_info_box.png")) {
    std::cerr << "attack info box texture failed to load!\n";
    abort();
  }
}

void AttackInfoBox::load_font() {
  if (!box_font.loadFromFile("font/lunchds.ttf")) {
    std::cerr << "failed to load attack info box font!\n";
    abort();
  }
}

int AttackInfoBox::get_unit_sprite_idx(const Unit &unit) {
  return std::visit(GetUnitSpriteId{}, unit);
}

void AttackInfoBox::set_position(int x, int y) {
  box_sprite.setPosition(x, y);
  update_attacking_unit_pos();
  update_attacked_unit_pos();
  update_box_text_pos();
  set_winner_highlight();
}

void AttackInfoBox::set_attacking_unit(const std::optional<Unit> &attacker) {
  if (!attacker) {
    return;
  }
  const auto attackerUnit = attacker.value();
  if (std::visit(GetOwner{}, attackerUnit) == Turn::PlayerA) {
    attacking_unit = *red_units_sprites_ptrs[get_unit_sprite_idx(attackerUnit)];
  } else {
    attacking_unit =
        *blue_units_sprites_ptrs[get_unit_sprite_idx(attackerUnit)];
  }
  attacking_unit.setPosition(attacking_unit_pos_x, attacking_unit_pos_y);
  attacking_unit.scale(1.5, 1.5);
  attacker_ptr = &attackerUnit;
}

void AttackInfoBox::set_attacked_unit(const std::optional<Unit> &victim) {
  if (!victim) {
    return;
  }
  const auto victimUnit = victim.value();
  if (std::visit(GetOwner{}, victimUnit) == Turn::PlayerA) {
    attacked_unit = *red_units_sprites_ptrs[get_unit_sprite_idx(victimUnit)];
  } else {
    attacked_unit = *blue_units_sprites_ptrs[get_unit_sprite_idx(victimUnit)];
  }
  attacked_unit.setPosition(attacked_unit_pos_x, attacked_unit_pos_y);
  attacked_unit.scale(1.5, 1.5);
  attacked_ptr = &victimUnit;
}

void AttackInfoBox::update_attacking_unit_pos() {
  attacking_unit_pos_x = box_sprite.getPosition().x + (get_width() / 4);
  attacking_unit_pos_y =
      box_sprite.getPosition().y +
      ((get_height() - attacking_unit.getGlobalBounds().height) / 2);
  attacking_unit.setPosition(attacking_unit_pos_x, attacking_unit_pos_y);
}

void AttackInfoBox::update_attacked_unit_pos() {
  attacked_unit_pos_x = box_sprite.getPosition().x + get_width() * 3 / 4 -
                        attacked_unit.getGlobalBounds().width;
  attacked_unit_pos_y = attacking_unit_pos_y;
  attacked_unit.setPosition(attacked_unit_pos_x, attacked_unit_pos_y);
}

void AttackInfoBox::update_box_text_pos() {
  box_text.setPosition(
      box_sprite.getPosition().x +
          ((get_width() - box_text.getLocalBounds().width) / 2),
      box_sprite.getPosition().y +
          (get_height() - box_text.getCharacterSize()) / 2);
}

const Unit *AttackInfoBox::get_winner() {
  if (!attacked_ptr || !attacker_ptr) {
    return {};
  }
  const auto result = std::visit(Attack{}, *attacker_ptr, *attacked_ptr);
  if (result == attack::Result::Won) {
    return attacker_ptr;
  }
  if (result == attack::Result::Lost) {
    return attacked_ptr;
  }
  // FIXME: what happens with a Draw? Both are winners then
  return {};
}

void AttackInfoBox::set_winner_highlight() {
  if (get_winner() == attacker_ptr) {
    winner_highlight.setPosition(attacking_unit.getPosition());
  }
  if (get_winner() == attacked_ptr) {
    winner_highlight.setPosition(attacked_unit.getPosition());
  }
}

void AttackInfoBox::draw_winner_highlight(sf::RenderWindow &win) {
  if (!get_winner()) {
    return;
  }
  winner_highlight.setScale(1.5, 1.5);
  win.draw(winner_highlight);
  winner_highlight.setScale(1, 1);
}