#pragma once
#include "Unit.hpp"

enum class TURN;
enum class RESULT;
class RegularUnit : public Unit {
public:
    RegularUnit(int v, TURN player)
        : Unit(v, "regular", player, true) {}
    virtual ~RegularUnit() {}
    // virtual bool can_move(int col, int row) const override {
    //     return Unit::can_move(col, row);
    // }
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        return Unit::attack(rhs);
    }
};
