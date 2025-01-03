#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class BombUnit : public Unit {
public:
    BombUnit(Turn player);
    bool can_move(const Tile &from, const Tile &to) const override;
};
