#pragma once

#include "unit/Movable.hpp"
#include "unit/Unit.hpp"

enum class Turn;
class MinerUnit : public Unit, public Movable {
public:
    MinerUnit(Turn player)
        : Unit(3, "miner", player, true), Movable(this){};
    virtual ~MinerUnit(){};
    virtual Result attack(const std::shared_ptr<Unit>& rhs) const override {
        if (rhs->get_type() == "bomb") {
            return Result::Won;
        }
        return Movable::attack(rhs);
    };
    bool can_move(int from_x, int from_y, int to_x, int to_y) const override {
        return Movable::can_move(from_x, from_y, to_x, to_y);
    };
};
