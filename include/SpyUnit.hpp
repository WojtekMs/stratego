#pragma once

#include "Unit.hpp"

enum class TURN;
class SpyUnit : public Unit {
public:
    SpyUnit(TURN player)
        : Unit(-1, "spy", player, true) {}
    virtual ~SpyUnit() {}
    // virtual bool can_move(int col, int row) const override {
    //     return Unit::can_move(col, row);
    // }
    virtual RESULT attack(const Unit& rhs) override {
        if (rhs.get_value() == 10) {
            return RESULT::WON;
        }
        return Unit::attack(rhs);
    }
};