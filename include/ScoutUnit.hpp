#pragma once
#include "Unit.hpp"

enum class TURN;
class ScoutUnit : public Unit {
public:
    ScoutUnit(TURN player)
        : Unit(2, "scout", player, true){}
    virtual ~ScoutUnit() {}
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        return Unit::attack(rhs);
    }
};