#pragma once

#include <memory>
#include <string>

enum class RESULT {
    LOST,
    DRAW,
    WON,
};
class Board;
enum class TURN;

class Unit {
    int value;
    std::string type;
    TURN owner;
    bool is_movable;

public:
    Unit(){};
    Unit(int v, const std::string& t, TURN player, bool m)
        : value(v), type(t), owner(player), is_movable(m) {
    };
    inline Unit(const Unit& rhs);
    inline virtual RESULT attack(const std::shared_ptr<Unit>& rhs) = 0;
    int get_value() const { return value; };
    std::string get_type() const { return type; };
    TURN get_owner() const { return owner; };
    bool get_movable() const { return is_movable; };
    virtual ~Unit(){};
};

Unit::Unit(const Unit& rhs) {
    value = rhs.value;
    type = rhs.type;
    owner = rhs.owner;
    is_movable = rhs.is_movable;
}

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

