#include "unit/ScoutUnit.hpp"

ScoutUnit::ScoutUnit(Turn player)
    : Unit(2, "scout", player) {};

bool ScoutUnit::can_move(const Tile &from, const Tile &to) const
{
    if (from.x == to.x)
    {
        return true;
    }
    if (from.y == to.y)
    {
        return true;
    }
    return false;
};
