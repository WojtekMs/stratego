#pragma once

#include "Unit.hpp"

enum class TURN;
class FlagUnit : public Unit {
public:
    FlagUnit(TURN player)
        : Unit(-1, "flag", player, false){};
    virtual ~FlagUnit(){};
    // virtual bool can_move(int col, int row) const override { return false; };
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override { return RESULT::LOST; };
};