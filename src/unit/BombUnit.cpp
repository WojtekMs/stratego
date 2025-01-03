#include "unit/BombUnit.hpp"

BombUnit::BombUnit(Turn player)
    : Unit(-1, "bomb", player) {};

bool BombUnit::can_move(const Tile &, const Tile &) const { return false; }
