#include "Board.hpp"

#include <iostream>
#include <map>
#include <string>

#include "BombUnit.hpp"
#include "FlagUnit.hpp"
#include "MarshalUnit.hpp"  // -> perhaps is unnecesary
#include "MinerUnit.hpp"
#include "RegularUnit.hpp"
#include "ScoutUnit.hpp"
#include "SpyUnit.hpp"

Board::Board()
    : height(12),
      width(10),
      units(width, height)
{
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

std::string Board::get_tile_info(int col, int row) const {
    for (size_t i = 0; i < obstacles.size(); ++i) {
        if (obstacles[i].x == col && obstacles[i].y == row) {
            return "O";
        }
    }
    if (units[row][col] != nullptr) {
        return units[row][col]->get_type();
    }
    return " ";
}

void Board::draw() {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::cout << "[ ";
            if (get_tile_info(col, row) == "regular") {
                std::cout << "R";
            } else if (get_tile_info(col, row) == "O") {
                std::cout << "O";
            } else if (get_tile_info(col, row) == "bomb") {
                std::cout << "B";
            } else if (get_tile_info(col, row) == "miner") {
                std::cout << "M";
            } else {
                std::cout << " ";
            }
            std::cout << " ]";
        }
        std::cout << '\n';
    }
}

void Board::set_unit(int col, int row, TURN player, int choice) {
    if (col < 0 || col >= width) {
        return;
    }
    if (row < (height - 5) || row >= height) {
        return;
    }
    if (get_tile_info(col, row) != " ") {
        return;
    }

    //first we have to choose the type of unit to set
    switch (choice) {
    case 1: {
        units[row][col] = std::make_shared<RegularUnit>(5, player);
    } break;
    case 2: {
        units[row][col] = std::make_shared<BombUnit>(player);
    } break;
    case 3: {
        units[row][col] = std::make_shared<MinerUnit>(player);
    } break;
        // case 4: {
        //     units[row][col] = std::make_shared<FlagUnit>(5, player);
        // } break;
        // case 5: {
        //     units[row][col] = std::make_shared<SpyUnit>(5, player);
        // } break;
        // case 6: {
        //     units[row][col] = std::make_shared<ScoutUnit>(5, player);
        // } break;
    }
    std::cout << "unit created type: " << units[row][col]->get_type() << '\n';
    std::cout << "unit created owner: " << static_cast<int>(units[row][col]->get_owner()) << '\n';
    //second we set the desired field with the chosen unit
    units[row][col]->set_position(col, row);
}

void Board::remove_unit(int col, int row) {
    units[row][col].reset();
}

void Board::move_unit(std::pair<int, int> from, std::pair<int, int> to) {
    //under the condition that:
    // -- the field we move to is empty
    // -- the field we want move from has a unit
    // -- the field we move from is on map
    // -- the field we move to is on map
    units[to.second][to.first].swap(units[from.second][from.first]);
}

Board::tile Board::point_reflection(int col, int row) {
    Board::tile distance;
    Board::tile distance_point;
    Board::tile reflection;
    Board::tile reflection_point;
    if (col >= 5 && row <= 5) {  //first quarter of the board
        distance_point = Board::tile(4, 6);
        reflection_point = Board::tile(5, 5);
    }
    if (col <= 4 && row <= 5) {  //second quarter of the board
        distance_point = Board::tile(5, 6);
        reflection_point = Board::tile(4, 5);
    }
    if (col <= 4 && row >= 6) {  //third quarter of the board
        distance_point = Board::tile(5, 5);
        reflection_point = Board::tile(4, 6);
    }
    if (col >= 5 && row >= 6) {  //fourth quarter of the board
        distance_point = Board::tile(4, 5);
        reflection_point = Board::tile(5, 6);
    }
    distance.x = col - distance_point.x;
    distance.y = row - distance_point.y;
    reflection.x = -distance.x;
    reflection.y = -distance.y;
    return Board::tile(reflection_point.x + reflection.x, reflection_point.y + reflection.y);
}

Board& Board::operator=(const Board& rhs) {
    if (this == &rhs) {
        return *this;
    }
    height = rhs.height;
    width = rhs.width;
    set_default_units();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (!rhs.units[row][col].get()) {
                continue;
            }
            if (rhs.units[row][col]->get_type() == "regular") {
                units[row][col] = std::make_shared<RegularUnit>(*rhs.units[row][col]);
            }
            if (rhs.units[row][col]->get_type() == "bomb") {
                units[row][col] = std::make_shared<BombUnit>(*rhs.units[row][col]);
            }
            if (rhs.units[row][col]->get_type() == "miner") {
                units[row][col] = std::make_shared<MinerUnit>(*rhs.units[row][col]);
            }
            // if (rhs.units[row][col]->get_type() == "flag") {
            //     units[row][col] = std::make_shared<FlagUnit>(*rhs.units[row][col]);
            // }
            // if (rhs.units[row][col]->get_type() == "spy") {
            //     units[row][col] = std::make_shared<SpyUnit>(*rhs.units[row][col]);
            // }
            // if (rhs.units[row][col]->get_type() == "scout") {
            //     units[row][col] = std::make_shared<ScoutUnit>(*rhs.units[row][col]);
            // }
        }
    }
    for (int i = 0; i < obstacles.size(); ++i) {
        obstacles[i] = rhs.obstacles[i];
    }
    return *this;
}

void Board::update(const Board& other_board) {
    Board::tile other_unit;
    *this = other_board;
    for (int row = 0; row < height / 2; ++row) {
        for (int col = 0; col < width; ++col) {
            other_unit = point_reflection(col, row);
            units[other_unit.y][other_unit.x].swap(units[row][col]);
        }
    }
}