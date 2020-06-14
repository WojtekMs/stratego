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

enum class STATE {
    UNINITIALIZED,
    INITIALIZED,
};

constexpr int MAX_UNIT_COUNT = 40;


class Board {
    struct Tile {
        int x;
        int y;
        explicit Tile(int col = 0, int row = 0) { x = col; y = row; };
        Tile& operator=(const Tile& rhs) {x = rhs.x; y = rhs.y; };
    };

    int height;
    int width;
    STATE current_state;
    int unit_count;
    Array2D<std::shared_ptr<Unit>> units;
    std::array<Tile, 8> obstacles;

    void set_default_units();
    void set_obstacles();
    Tile point_reflection(int col, int row);
    bool out_of_range(int col, int row) const;

public:
    Board();
    void draw() const;
    bool set_unit(int col, int row, TURN player, int choice);
    void remove_unit(int col, int row);
    std::string get_tile_info(int col, int row) const;
    int get_height() const { return height; };
    int get_width() const { return width; };
    std::shared_ptr<Unit> get_unit(int col, int row) const { return units[row][col]; };
    bool can_move(Tile from, Tile to) const;
    void move_unit(Tile from, Tile to);
    void reverse_move_unit(Tile from, Tile to);
    void update(const Board& other_board);
    Board& operator=(const Board& rhs);
    STATE get_state() const { return current_state; };

};