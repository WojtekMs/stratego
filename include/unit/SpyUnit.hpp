#pragma once

#include "unit/Unit.hpp"
#include "unit/Movable.hpp"

enum class Turn;
class SpyUnit : public Unit, public Movable {
public:
    SpyUnit(Turn player)
        : Unit(-1, "spy", player, true), Movable(this) {};
    virtual ~SpyUnit() {};
    Result attack(const std::shared_ptr<Unit>& rhs) const override {
        if (rhs->get_value() == 10) {
            return Result::Won;
        }
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        return Movable::can_move(from_x, from_y, to_x, to_y);
    };
};
