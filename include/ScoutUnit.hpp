#pragma once
#include "Unit.hpp"

enum class TURN;
class ScoutUnit : public Unit {
public:
    ScoutUnit(TURN player)
        : Unit(2, "scout", player, true){}
    virtual ~ScoutUnit() {}
    // virtual bool can_move(int col, int row) const override {
    //     if (col == get_x()) {
    //         return true;
    //     }
    //     if (row == get_y()) {
    //         return true;
    //     }
    //     return false;
    // }
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        return Unit::attack(rhs);
    }
};