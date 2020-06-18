#include "Board.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "BombUnit.hpp"
#include "FlagUnit.hpp"
#include "MinerUnit.hpp"
#include "RegularUnit.hpp"
#include "ScoutUnit.hpp"
#include "SpyUnit.hpp"

Board::Board()
    : height(12),
      width(10),
      current_state(STATE::UNINITIALIZED),
      unit_count(0),
      units(width, height),
      max_count_of_each_unit({{"flag", 1},
                              {"scout", 8},
                              {"miner", 5},
                              {"bomb", 6},
                              {"spy", 1},
                              {"regular4", 4},
                              {"regular5", 4},
                              {"regular6", 4},
                              {"regular7", 3},
                              {"regular8", 2},
                              {"regular9", 1},
                              {"regular10", 1}}) {
    set_obstacles();
    set_default_units();
}

void Board::set_default_units() {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            units[row][col].reset();
            units[row][col] = nullptr;
        }
    }
}

void Board::set_obstacles() {
    int left_obstacle_x = 2;
    int obstacle_y = 5;
    int right_obstacle_x = 6;
    int j = 0;
    for (size_t i = 0; i < obstacles.size(); ++i) {
        if (i % 2 == 0) {
            j = 0;
        }
        if (i < 2) {
            obstacles[i].x = left_obstacle_x + j;
            obstacles[i].y = obstacle_y;
        }
        if (i > 1 && i < 4) {
            obstacles[i].x = left_obstacle_x + j;
            obstacles[i].y = obstacle_y + 1;
        }
        if (i > 3 && i < 6) {
            obstacles[i].x = right_obstacle_x + j;
            obstacles[i].y = obstacle_y;
        }
        if (i > 5 && i < 8) {
            obstacles[i].x = right_obstacle_x + j;
            obstacles[i].y = obstacle_y + 1;
        }
        j++;
    }
}

bool Board::out_of_range(int col, int row) const {
    if (col < 0 || col >= width) {
        return true;
    }
    if (row < 0 || row >= height) {
        return true;
    }
    return false;
}

std::string Board::get_tile_info(int col, int row, TURN player) const {
    if (out_of_range(col, row)) {
        return "#";
    }
    if (std::find_if(obstacles.begin(), obstacles.end(), [col, row](const Board::Tile& tile) {
            return tile.x == col && tile.y == row;
        }) != obstacles.end()) {
        return "O";
    }
    if (units[row][col]) {
        if (units[row][col]->get_owner() != player) {
            return "enemy";
        } else {
            return units[row][col]->get_type();
        }
    }
    return " ";
}

std::string Board::get_tile_info(Tile tile, TURN player) const {
    return get_tile_info(tile.x, tile.y, player);
}

int Board::get_max_unit_count(int idx) const {
    switch (idx) {
    case 0:
        return max_count_of_each_unit.at("scout");
    case 1:
        return max_count_of_each_unit.at("miner");
    case 2:
        return max_count_of_each_unit.at("regular4");
    case 3:
        return max_count_of_each_unit.at("regular5");
    case 4:
        return max_count_of_each_unit.at("regular6");
    case 5:
        return max_count_of_each_unit.at("regular7");
    case 6:
        return max_count_of_each_unit.at("regular8");
    case 7:
        return max_count_of_each_unit.at("regular9");
    case 8:
        return max_count_of_each_unit.at("regular10");
    case 9:
        return max_count_of_each_unit.at("bomb");
    case 10:
        return max_count_of_each_unit.at("flag");
    case 11:
        return max_count_of_each_unit.at("spy");
    }
    return -1;
}

void Board::set_state(STATE state) {
    current_state = state;
}

bool Board::set_unit(int col, int row, TURN player, int choice) {
    if (col < 0 || col >= width) {
        return false;
    }
    if (row < (height - 4) || row >= height) {
        return false;
    }
    if (choice < 0 && choice >= 12) {
        return false;
    }
    if (get_tile_info(col, row, player) != " ") {
        return false;
    }
    if (current_state == STATE::FULL) {
        return false;
    }

    //first we have to choose the type of unit to set
    switch (choice + 2) {
    case 2: {
        units[row][col] = std::make_shared<ScoutUnit>(player);
    } break;
    case 3: {
        units[row][col] = std::make_shared<MinerUnit>(player);
    } break;
    case 11: {
        units[row][col] = std::make_shared<BombUnit>(player);
    } break;
    case 12: {
        units[row][col] = std::make_shared<FlagUnit>(player);
    } break;
    case 13: {
        units[row][col] = std::make_shared<SpyUnit>(player);
    }
    }
    if (choice + 2 > 3 && choice + 2 < 11) {
        units[row][col] = std::make_shared<RegularUnit>(choice + 2, player);
    }
    std::cout << "unit created type: " << units[row][col]->get_type() << '\n';
    std::cout << "unit created value: " << units[row][col]->get_value() << '\n';
    std::cout << "unit created owner: " << static_cast<int>(units[row][col]->get_owner()) << '\n';
    //second we set the desired field with the chosen unit
    units[row][col]->set_position(col, row);
    unit_count++;
    if (unit_count == MAX_UNIT_COUNT) {
        current_state = STATE::FULL;
    }
    return true;
}

void Board::remove_unit(int col, int row) {
    units[row][col].reset();
    unit_count--;
    if (current_state == STATE::FULL) {
        current_state = STATE::UNINITIALIZED;
    }
}

bool Board::can_move(Tile from, Tile to) const {
    if (out_of_range(from.x, from.y)) {
        return false;
    }
    if (!units[from.y][from.x]) {
        return false;
    }
    if (!units[from.y][from.x]->get_movable()) {
        return false;
    }
    // if (!units[from.y][from.x]->can_move(to.x, to.y)) {
    //     return false;
    // }
    return true;
}

bool Board::move_unit(Tile from, Tile to) {
    if (can_move(from, to)) {
        units[from.y][from.x].swap(units[to.y][to.x]);
        // units[to.y][to.x]->set_position(to.x, to.y);
        return true;
    }
    return false;
}

void Board::reverse_move_unit(Tile from, Tile to) {
    Tile rev_from = point_reflection(from.x, from.y);
    Tile rev_to = point_reflection(to.x, to.y);
    std::shared_ptr<Unit> temp_ptr = units[rev_from.y][rev_from.x]; //<---- this does! (whaaat?)
    units[rev_from.y][rev_from.x] = units[rev_to.y][rev_to.x];
    units[rev_to.y][rev_to.x] = temp_ptr;
    // units[rev_from.y][rev_from.y].swap(units[rev_to.y][rev_to.x]); <---- this doesnt work!
}

Board::Tile Board::point_reflection(int col, int row) {
    Board::Tile distance;
    Board::Tile distance_point;
    Board::Tile reflection;
    Board::Tile reflection_point;
    if (col >= 5 && row <= 5) {  //first quarter of the board
        distance_point = Board::Tile(4, 6);
        reflection_point = Board::Tile(5, 5);
    }
    if (col <= 4 && row <= 5) {  //second quarter of the board
        distance_point = Board::Tile(5, 6);
        reflection_point = Board::Tile(4, 5);
    }
    if (col <= 4 && row >= 6) {  //third quarter of the board
        distance_point = Board::Tile(5, 5);
        reflection_point = Board::Tile(4, 6);
    }
    if (col >= 5 && row >= 6) {  //fourth quarter of the board
        distance_point = Board::Tile(4, 5);
        reflection_point = Board::Tile(5, 6);
    }
    distance.x = col - distance_point.x;
    distance.y = row - distance_point.y;
    reflection.x = -distance.x;
    reflection.y = -distance.y;
    if (out_of_range(reflection_point.x + reflection.x, reflection_point.y + reflection.y)) {
        std::cerr << " reflection points out of range! inside update_board\n";
        abort();
    }
    return Board::Tile(reflection_point.x + reflection.x, reflection_point.y + reflection.y);
}

Board& Board::operator=(const Board& rhs) {
    if (this == &rhs) {
        return *this;
    }
    height = rhs.height;
    width = rhs.width;
    // set_default_units();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            units[row][col] = rhs.units[row][col];
        }
    }
    for (size_t i = 0; i < obstacles.size(); ++i) {
        obstacles[i] = rhs.obstacles[i];
    }
    return *this;
}

void Board::update(const Board& other_board) {
    Board::Tile other_unit;
    *this = other_board;
    for (int row = 0; row < height / 2; ++row) {
        for (int col = 0; col < width; ++col) {
            other_unit = point_reflection(col, row);
            units[other_unit.y][other_unit.x].swap(units[row][col]);
        }
    }
}

std::shared_ptr<Unit> Board::get_unit(int col, int row) const {
    if (out_of_range(col, row)) {
        return std::shared_ptr<Unit>{};
    }
    return units[row][col];
}

std::shared_ptr<Unit> Board::get_unit(Board::Tile chosen_unit) const {
    if (out_of_range(chosen_unit.x, chosen_unit.y)) {
        return std::shared_ptr<Unit>{};
    }
    return units[chosen_unit.y][chosen_unit.x];
}