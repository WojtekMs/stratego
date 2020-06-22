#pragma once

#include "Board.hpp"

class Movable {
public:
    inline virtual bool can_move(int from_x, int from_y, int to_x, int to_y) const = 0;
    virtual bool can_move(const Board::Tile& from, const Board::Tile& to) const { return can_move(from.x, from.y, to.x, to.y); };
    virtual ~Movable(){};
};

bool Movable::can_move(int from_x, int from_y, int to_x, int to_y) const {
    if (from_x + 1 == to_x && from_y == to_y) {
        return true;
    }
    if (from_x - 1 == to_x && from_y == to_y) {
        return true;
    }
    if (from_x == to_x && from_y + 1 == to_y) {
        return true;
    }
    if (from_x == to_x && from_y - 1 == to_y) {
        return true;
    }
    return false;
}