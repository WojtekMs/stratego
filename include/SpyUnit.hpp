#pragma once

#include "Unit.hpp"
#include "Movable.hpp"

enum class TURN;
class SpyUnit : public Unit, public Movable {
public:
    SpyUnit(TURN player)
        : Unit(-1, "spy", player, true), Movable(this) {};
    virtual ~SpyUnit() {};
    RESULT attack(const std::shared_ptr<Unit>& rhs) const override {
        if (rhs->get_value() == 10) {
            return RESULT::WON;
        }
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        return Movable::can_move(from_x, from_y, to_x, to_y);
    };
};
