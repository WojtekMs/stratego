#pragma once
#include "Array2D.h"
#include <vector>
#include <array>
#include <string>
#include "Unit.hpp"


enum class TURN {
    PLAYER_A,
    PLAYER_B
};

class Board
{
    struct obstacle {
        int x;
        int y;
    };
    int height;
    int width;
    Array2D<Unit *> units;
    Array2D<bool> has_unit;
    std::array<obstacle, 8> obstacles;

    // std::vector<std::vector<char>> has_unit;
    void set_units();
    void set_obstacles();
    

public:
    Board();
    void draw();
    void set_unit(int col, int row, TURN player);
    void remove_unit(int col, int row);
    std::string get_tile_info(int col, int row) const;
    int get_height() const {return height; };
    int get_width() const {return width; };
    Unit* get_unit(int col, int row) const { return units[row][col]; };

};