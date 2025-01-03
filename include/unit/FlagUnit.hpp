#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class FlagUnit : public Unit
{
public:
    FlagUnit(Turn player);
    bool can_move(const Tile &from, const Tile &to) const override;
};