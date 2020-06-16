#pragma once
#include "Unit.hpp"

enum class TURN;
enum class RESULT;
class RegularUnit : public Unit {
public:
    RegularUnit(int v, TURN player)
        : Unit(v, "regular", player) {}
    virtual ~RegularUnit() {}
    virtual bool can_move(int col, int row) const override {
        return Unit::can_move(col, row);
    }
    virtual RESULT attack(const Unit& rhs) override {
        return Unit::attack(rhs);
    }
};
