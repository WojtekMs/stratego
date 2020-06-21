#pragma once
#include "Unit.hpp"

enum class TURN;
class MinerUnit : public Unit {
public:
    MinerUnit(TURN player)
        : Unit(3, "miner", player, true){};
    virtual ~MinerUnit(){};
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        if (rhs->get_type() == "bomb") {
            return RESULT::WON;
        }
        return Unit::attack(rhs);
    }
};