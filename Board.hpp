#pragma once
#include "Array2D.h"
#include <vector>
#include <array>

class Board
{
    struct obstacle {
        int x;
        int y;
    };
    int height;
    int width;
    Array2D<bool> has_unit;
    std::array<obstacle, 8> obstacles;

    // std::vector<std::vector<char>> has_unit;
    void set_units();
    void set_obstacles();
    

public:
    Board();
    void draw();
    void set_unit(int col, int row);
    char get_tile_info(int col, int row) const;
};