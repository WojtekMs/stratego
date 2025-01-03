#include "unit/FlagUnit.hpp"

FlagUnit::FlagUnit(Turn player)
    : Unit(-1, "flag", player) {};

bool FlagUnit::can_move(const Tile &, const Tile &) const { return false; }
