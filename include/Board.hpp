#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Array2D.h"
#include "Tile.hpp"

enum class TURN {
    PLAYER_A,
    PLAYER_B
};

enum class STATE {
    UNINITIALIZED,
    INITIALIZED,
    FULL,
};

constexpr int MAX_UNIT_COUNT = 40;

class Unit;
class Board {
private:
    int height;
    int width;
    STATE current_state;
    int unit_count;
    Array2D<std::shared_ptr<Unit>> units;
    std::array<Tile, 8> obstacles;
    const std::map<std::string, int> max_count_of_each_unit;

    void set_default_units();
    void set_obstacles();
    Tile point_reflection(int col, int row);
    bool out_of_range(int col, int row) const;
    void set_state(STATE state);

public:
    Board();
    bool set_unit(int col, int row, TURN player, int choice);
    void remove_unit(int col, int row);
    void reverse_remove_unit(int col, int row);
    std::string get_tile_info(int col, int row, TURN player) const;
    std::string get_tile_info(const Tile& tile, TURN player) const;
    int get_height() const { return height; };
    int get_width() const { return width; };
    std::shared_ptr<Unit> get_unit(int col, int row) const;
    std::shared_ptr<Unit> get_unit(const Tile& chosen_unit) const;
    bool can_move(const Tile& from, const Tile& to) const;
    bool move_unit(const Tile& from, const Tile& to);
    void reverse_move_unit(const Tile& from, const Tile& to);
    void update(const Board& other_board);
    Board& operator=(const Board& rhs);
    STATE get_state() const { return current_state; };
    int get_max_unit_count(const std::string& unit_type) const { return max_count_of_each_unit.at(unit_type); };
    int get_max_unit_count(int idx) const;

};