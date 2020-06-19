#pragma once

#include "Unit.hpp"
#include "Movable.hpp"

enum class TURN;
class SpyUnit : public Unit, public Movable {
public:
    SpyUnit(TURN player)
        : Unit(-1, "spy", player, true) {}
    virtual ~SpyUnit() {}
    virtual bool can_move(Board::Tile from, Board::Tile to) const override {
        return Movable::can_move(from, to);
    }
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) override {
        if (rhs->get_value() == 10) {
            return RESULT::WON;
        }
        return Unit::attack(rhs);
    }
};