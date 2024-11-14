#pragma once

#include <memory>
#include <string>

#include "unit/Movable.hpp"

class Board;
enum class Turn;

class Unit : public Movable::Delegate {
    int value{};
    std::string type{};
    Turn owner{};

public:
    Unit() = default;
    Unit(int v, const std::string& t, Turn player, bool m)
        : value(v), type(t), owner(player) {
    };
    int get_value() const override { return value; };
    std::string get_type() const { return type; };
    Turn get_owner() const { return owner; };
    virtual ~Unit() = default;
};


