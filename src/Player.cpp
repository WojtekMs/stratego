#include "Player.hpp"

#include <stdexcept>

#include "unit/Unit.hpp"
#include "unit/visit/Attack.hpp"
#include "unit/visit/GetOwner.hpp"

void Player::set_unit(int col, int row, int choice) {
    board.set_unit(col, row, player, choice);
}

void Player::remove_unit(int col, int row) {
    if (board.get_unit(col, row)) {
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
    return std::visit(Attack{}, attacker_unit.value(), attacked_unit.value());
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
        if (std::visit(GetOwner{}, board.get_unit(to.x, to.y).value()) == player) {
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
        return ScoutUnit::get_count();
    case 1:
        return MinerUnit::get_count();
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        return RegularUnit::get_count(idx + 2);
    case 9:
        return BombUnit::get_count();
    case 10:
        return FlagUnit::get_count();
    case 11:
        return SpyUnit::get_count();
    }
    return -1;
}
