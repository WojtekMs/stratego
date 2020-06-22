#pragma once

#include <memory>
#include <string>

#include "Movable.hpp"

class Board;
enum class TURN;

class Unit : public Movable::Delegate {
    int value;
    std::string type;
    TURN owner;

public:
    Unit(){};
    Unit(int v, const std::string& t, TURN player, bool m)
        : value(v), type(t), owner(player) {
    };
    inline Unit(const Unit& rhs);
    int get_value() const override { return value; };
    std::string get_type() const { return type; };
    TURN get_owner() const { return owner; };
    virtual ~Unit(){};
};

Unit::Unit(const Unit& rhs) {
    value = rhs.value;
    type = rhs.type;
    owner = rhs.owner;
}
