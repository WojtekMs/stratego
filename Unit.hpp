#pragma once
#include <string>

enum class RESULT {
    LOST,
    DRAW,
    WON
};

enum class TURN;
class Unit {
    int value;
    std::string type;
    TURN owner;
    int x;
    int y;

public:
    Unit(){};
    Unit(int v, const std::string& t, TURN player)
        : value(v), type(t), owner(player) {
        x = -1;
        y = -1;
    };
    inline Unit(const Unit& rhs);
    inline virtual bool can_move(int col, int row) const = 0;
    inline virtual RESULT attack(const Unit& rhs) = 0;
    int get_value() const { return value; };
    std::string get_type() const { return type; };
    int get_x() const { return x; };
    int get_y() const { return y; };
    TURN get_owner() const { return owner; };
    inline void set_position(int Ax, int Ay);
    virtual ~Unit(){};
};

Unit::Unit(const Unit& rhs) {
    value = rhs.value;
    type = rhs.type;
    owner = rhs.owner;
    x = rhs.x;
    y = rhs.y;
}

void Unit::set_position(int Ax, int Ay) {
    x = Ax;
    y = Ay;
}

bool Unit::can_move(int col, int row) const {
    if (col == get_x() + 1 && row == get_y()) {
        return true;
    }
    if (col == get_x() - 1 && row == get_y()) {
        return true;
    }
    if (row == get_y() + 1 && col == get_x()) {
        return true;
    }
    if (row == get_y() - 1 && col == get_x()) {
        return true;
    }
    return false;
}

RESULT Unit::attack(const Unit& rhs) {
    if (rhs.get_type() == "bomb") {
        return RESULT::LOST;
    }
    if (get_value() > rhs.get_value()) {
        return RESULT::WON;
    }
    if (get_value() == rhs.get_value()) {
        return RESULT::DRAW;
    }
    if (get_value() < rhs.get_value()) {
        return RESULT::LOST;
    }
}
