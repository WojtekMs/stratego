#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class ScoutUnit : public Unit
{
public:
    ScoutUnit(Turn player);
    bool can_move(const Tile &from, const Tile &to) const override;
};