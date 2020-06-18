#pragma once

#include "Unit.hpp"

enum class TURN;
class BombUnit : public Unit {
public:
    BombUnit(TURN player)
        : Unit(0, "bomb", player, false){};
    virtual ~BombUnit(){};
    // virtual bool can_move(int col, int row) const override { return false; };
    virtual RESULT attack(const Unit& rhs) override {
        return RESULT::LOST;
    }
};
