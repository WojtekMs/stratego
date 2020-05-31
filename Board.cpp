#include "Board.hpp"
#include "RegularUnit.hpp"
#include <iostream>
#include <map>
#include <string>

Board::Board()
    : height(12),
      width(10),
      units(width, height),
      has_unit(width, height)
{
    // RegularUnit unit(5);
    // units.push_back(&unit);
    set_obstacles();
    set_units();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            units[row][col] = nullptr;
        }
    }
}

void Board::set_units()
{
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            has_unit[row][col] = false;
        }
    }
    // for (auto & row : has_unit) {
    //     for (auto & col : row) {
    //         col = 1;
    //     }
    // }
}

void Board::set_obstacles()
{
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

    // for (int row = 0; row < height; ++row) {
    //     for (int col = 0; col < width; ++col) {
    //         if
    //     }
    // }
    // obstacles[0].x = 2;
    // obstacles[0].y = 5;
    // obstacles[1].x = 4;
    // obstacles[1].y = 6;
    // obstacles[2].x = 3;
    // obstacles[2].y = 7;
    // obstacles[3].x = 4;
    // obstacles[3].y = 7;

    // obstacles[4].x = 6;
    // obstacles[4].y = 6;
    // obstacles[5].x = 7;
    // obstacles[5].y = 6;
    // obstacles[6].x = 6;
    // obstacles[6].y = 7;
    // obstacles[7].x = 7;
    // obstacles[7].y = 7;
    // for (size_t i = 0; i < obstacles.size(); ++i) {
    //     obstacles[i].x = 3 + i;
    //     obstacles[i].y = 6 + i;
    // }
}

std::string Board::get_tile_info(int col, int row) const
{

    for (size_t i = 0; i < obstacles.size(); ++i) {
        if (obstacles[i].x == col && obstacles[i].y == row) {
            return "O";
        }
    }
    if (units[row][col] != nullptr) {
        return units[row][col]->get_type();
    }
    // if (units[0]->get_x() == col && units[0]->get_y() == row) {
    //     return units[0]->get_type();
    // }
    return " ";
}

void Board::draw()
{
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::cout << "[ ";
            if (get_tile_info(col, row) == "regular") {
                std::cout << "R";
            } else if (get_tile_info(col, row) == "O") {
                std::cout << "O";
            }
            else {
                std::cout << " ";
            }
            std::cout << " ]";
           
            
        }
        std::cout << '\n';
    }
}

void Board::set_unit(int col, int row, TURN player) {
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


    //second we set the desired field with the chosen unit
    units[row][col] = new RegularUnit(5, player);
    units[row][col]->set_position(col, row);

}

void Board::remove_unit(int col, int row)
{
    delete units[row][col];
    units[row][col] = nullptr;
}