#include "Player.hpp"

void Player::set_units_count() {
    units_count.insert(std::pair<std::string, int>{"regular", 0});
    units_count.insert(std::pair<std::string, int>{"bomb", 0});
    units_count.insert(std::pair<std::string, int>{"miner", 0});
    units_count.insert(std::pair<std::string, int>{"flag", 0});
    units_count.insert(std::pair<std::string, int>{"spy", 0});
    units_count.insert(std::pair<std::string, int>{"scout", 0});
    units_count.insert(std::pair<std::string, int>{"marshal", 0});
}

void Player::set_unit(int col, int row, int choice) {
    // check if the variables are correct
    if (board.set_unit(col, row, player, choice)) {
    units_count[ board.get_unit(col, row)->get_type() ]++;
    }
}

void Player::remove_unit(int col, int row) {
    // check if the variables are correct
    units_count [ board.get_unit(col, row)->get_type() ]--;
    board.remove_unit(col, row);
}

void Player::move_unit(Board::Tile from, Board::Tile to) {
    // check if the variables are correct
    board.move_unit(from, to);
}

void Player::update_board(const Board& other_player_board) {
    board.update(other_player_board);    
}
