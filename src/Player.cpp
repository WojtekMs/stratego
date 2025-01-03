#include "unit/Unit.hpp"
#include "Player.hpp"
#include <stdexcept>
#include "Attack.h"

void Player::set_units_count() {
    units_count.insert(std::pair<std::string, int>{"regular4", 0});
    units_count.insert(std::pair<std::string, int>{"regular5", 0});
    units_count.insert(std::pair<std::string, int>{"regular6", 0});
    units_count.insert(std::pair<std::string, int>{"regular7", 0});
    units_count.insert(std::pair<std::string, int>{"regular8", 0});
    units_count.insert(std::pair<std::string, int>{"regular9", 0});
    units_count.insert(std::pair<std::string, int>{"regular10", 0});
    units_count.insert(std::pair<std::string, int>{"bomb", 0});
    units_count.insert(std::pair<std::string, int>{"miner", 0});
    units_count.insert(std::pair<std::string, int>{"flag", 0});
    units_count.insert(std::pair<std::string, int>{"spy", 0});
    units_count.insert(std::pair<std::string, int>{"scout", 0});
    units_count.insert(std::pair<std::string, int>{"marshal", 0});
}

void Player::set_unit(int col, int row, int choice) {
    if (board.set_unit(col, row, player, choice)) {
        std::shared_ptr<Unit> chosen_unit = board.get_unit(col, row);
        if (chosen_unit->get_type() == "regular") {
            units_count[chosen_unit->get_type() + std::to_string(chosen_unit->get_value())]++;
        }
        units_count[chosen_unit->get_type()]++;
    }
}

void Player::remove_unit(int col, int row) {
    if (board.get_unit(col, row)) {
        std::shared_ptr<Unit> temp_unit = board.get_unit(col, row);
        if (temp_unit->get_type() == "regular") {
            units_count[temp_unit->get_type() + std::to_string(temp_unit->get_value())]--;
        }
        units_count[board.get_unit(col, row)->get_type()]--;
        board.remove_unit(col, row);
    }
}

void Player::remove_unit(Tile chosen_unit) {
    remove_unit(chosen_unit.x, chosen_unit.y);
}

void Player::reverse_remove_unit(Tile unit) {
    board.reverse_remove_unit(unit.x, unit.y);
}

bool Player::move_unit(Tile from, Tile to) {
    return board.move_unit(from, to);
}

attack::Result Player::attack(Tile attacker, Tile attacked) {
    // TODO: make the actual implementation a strategy (use dependency injection)
    const auto& attacker_unit = board.get_unit(attacker);
    const auto& attacked_unit = board.get_unit(attacked);
    return attack::attack(attacker_unit, attacked_unit);
}

void Player::reverse_move_unit(Tile from, Tile to) {
    board.reverse_move_unit(from, to);
}

bool Player::can_move(Tile from, Tile to) {
    if (board.get_tile_info(to.x, to.y, player) == "#") {
        return false;
    }
    if (board.get_tile_info(to.x, to.y, player) == "O") {
        return false;
    }
    if (board.get_unit(to.x, to.y)) {
        if (board.get_unit(to.x, to.y)->get_owner() == player) {
            return false;
        }
    }
    if (!board.can_move(from, to)) {
        return false;
    }

    return true;
}

void Player::update_board(const Board& other_player_board) {
    board.update(other_player_board);
}

std::string Player::get_tile_info(int col, int row) const {
    return board.get_tile_info(col, row, player);
}

std::string Player::get_tile_info(Tile tile) const {
    return board.get_tile_info(tile, player);
}

int Player::get_units_count(int idx) {
    switch (idx) {
    case 0:
        return units_count.at("scout");
    case 1:
        return units_count.at("miner");
    case 2:
        return units_count.at("regular4");
    case 3:
        return units_count.at("regular5");
    case 4:
        return units_count.at("regular6");
    case 5:
        return units_count.at("regular7");
    case 6:
        return units_count.at("regular8");
    case 7:
        return units_count.at("regular9");
    case 8:
        return units_count.at("regular10");
    case 9:
        return units_count.at("bomb");
    case 10:
        return units_count.at("flag");
    case 11:
        return units_count.at("spy");
    }
    return -1;
}
