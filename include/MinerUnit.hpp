#pragma once
#include "Unit.hpp"

enum class TURN;
class MinerUnit : public Unit {
public:
    MinerUnit(TURN player)
        : Unit(3, "miner", player, true){};
    virtual ~MinerUnit(){};
    // virtual bool can_move(int col, int row) const override {
    //     return Unit::can_move(col, row);
    // }
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        if (rhs->get_type() == "bomb") {
            return RESULT::WON;
        }
        return Unit::attack(rhs);
    }
};