#pragma once

#include "unit/Unit.hpp"
#include "unit/Movable.hpp"

enum class TURN;
class ScoutUnit : public Unit, public Movable {
public:
    ScoutUnit(TURN player)
        : Unit(2, "scout", player, true), Movable(this) {};
    virtual ~ScoutUnit() {};
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) const override {
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        if (from_x == to_x) {
            return true;
        }
        if (from_y == to_y) {
            return true;
        }
        return false;
    };
};