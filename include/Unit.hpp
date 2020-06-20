#pragma once

#include <memory>
#include <string>

enum class RESULT {
    LOST,
    DRAW,
    WON,
};
class Board;
// class Board::Tile;
enum class TURN;

class Unit {
    int value;
    std::string type;
    TURN owner;
    bool is_movable;
    // int x;
    // int y;

public:
    Unit(){};
    Unit(int v, const std::string& t, TURN player, bool m)
        : value(v), type(t), owner(player), is_movable(m) {
        // x = -1;
        // y = -1;
    };
    inline Unit(const Unit& rhs);
    // inline virtual bool can_move(int col, int row) const = 0;
    inline virtual RESULT attack(const std::shared_ptr<Unit>& rhs) = 0;
    int get_value() const { return value; };
    std::string get_type() const { return type; };
    // int get_x() const { return x; };
    // int get_y() const { return y; };
    TURN get_owner() const { return owner; };
    bool get_movable() const { return is_movable; };
    // inline void set_position(int Ax, int Ay);
    virtual ~Unit(){};
};

Unit::Unit(const Unit& rhs) {
    value = rhs.value;
    type = rhs.type;
    owner = rhs.owner;
    is_movable = rhs.is_movable;
    // x = rhs.x;
    // y = rhs.y;
}

// void Unit::set_position(int Ax, int Ay) {
//     x = Ax;
//     y = Ay;
// }

// bool Unit::can_move(int col, int row) const {
//     if (col == get_x() + 1 && row == get_y()) {
//         return true;
//     }
//     if (col == get_x() - 1 && row == get_y()) {
//         return true;
//     }
//     if (row == get_y() + 1 && col == get_x()) {
//         return true;
//     }
//     if (row == get_y() - 1 && col == get_x()) {
//         return true;
//     }
//     return false;
// }

RESULT Unit::attack(const std::shared_ptr<Unit>& rhs) {
    if (rhs) {
        if (rhs->get_type() == "bomb") {
            return RESULT::LOST;
        }
        if (get_value() > rhs->get_value()) {
            return RESULT::WON;
        }
        if (get_value() == rhs->get_value()) {
            return RESULT::DRAW;
        }
        if (get_value() < rhs->get_value()) {
            return RESULT::LOST;
        }
    }
}



// bool Movable::can_move(Board::Tile from, Board::Tile to) const {
//     if (to.x == from.x + 1 && to.y == from.y) {
//         return true;
//     }
//     if (to.x == from.x - 1 && to.y == from.y) {
//         return true;
//     }
//     if (to.x == from.x && to.y == from.y + 1) {
//         return true;
//     }
//     if (to.x == from.x && to.y == from.y - 1) {
//         return true;
//     }
//     return false;
// }


