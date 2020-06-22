#pragma once

#include "Movable.hpp"
#include "Unit.hpp"

enum class TURN;
enum class RESULT;
class RegularUnit : public Unit, public Movable {
public:
    RegularUnit(int v, TURN player)
        : Unit(v, "regular", player, true), Movable(this) {};
    virtual ~RegularUnit() {};
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) const override {
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        Movable::can_move(from_x, from_y, to_x, to_y);
    };
};
