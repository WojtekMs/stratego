#pragma once
#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Array2D.h"
#include "Unit.hpp"

enum class TURN {
    PLAYER_A,
    PLAYER_B
};

class Board {
    struct tile {
        int x;
        int y;
        explicit tile(int col = 0, int row = 0) { x = col; y = row; };
        tile& operator=(const tile& rhs) {x = rhs.x; y = rhs.y; };
    };

    int height;
    int width;
    Array2D<std::shared_ptr<Unit>> units;
    std::array<tile, 8> obstacles;

    void set_default_units();
    void set_obstacles();
    tile point_reflection(int col, int row);

public:
    Board();
    void draw();
    void set_unit(int col, int row, TURN player, int choice);
    void remove_unit(int col, int row);
    std::string get_tile_info(int col, int row) const;
    int get_height() const { return height; };
    int get_width() const { return width; };
    std::shared_ptr<Unit> get_unit(int col, int row) const { return units[row][col]; };
    void move_unit(std::pair<int, int> from, std::pair<int, int> to);
    void update(const Board& other_board);
    Board& operator=(const Board& rhs);
};