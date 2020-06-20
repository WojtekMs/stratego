#pragma once

#include "Unit.hpp"

enum class TURN;
class SpyUnit : public Unit {
public:
    SpyUnit(TURN player)
        : Unit(-1, "spy", player, true) {}
    virtual ~SpyUnit() {}
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        if (rhs->get_value() == 10) {
            return RESULT::WON;
        }
        return Unit::attack(rhs);
    }
};