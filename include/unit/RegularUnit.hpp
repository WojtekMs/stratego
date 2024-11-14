#pragma once

#include "unit/Movable.hpp"
#include "unit/Unit.hpp"

enum class Turn;
enum class Result;
class RegularUnit : public Unit, public Movable {
public:
    RegularUnit(int v, Turn player)
        : Unit(v, "regular", player, true), Movable(this) {};
    virtual ~RegularUnit() {};
    virtual Result attack(const std::shared_ptr<Unit>& rhs) const override {
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        return Movable::can_move(from_x, from_y, to_x, to_y);
    };
};
