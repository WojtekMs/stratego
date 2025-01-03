#include "unit/Unit.hpp"

Unit::Unit(int value, std::string type, Turn player)
    : value_{value},
      type_{std::move(type)},
      owner_{player}
{
}

int Unit::get_value() const noexcept { return value_; };

std::string Unit::get_type() const noexcept { return type_; };

Turn Unit::get_owner() const noexcept { return owner_; };

bool Unit::can_move(const Tile &from, const Tile &to) const
{
    if (from.x + 1 == to.x && from.y == to.y)
    {
        return true;
    }
    if (from.x - 1 == to.x && from.y == to.y)
    {
        return true;
    }
    if (from.x == to.x && from.y + 1 == to.y)
    {
        return true;
    }
    if (from.x == to.x && from.y - 1 == to.y)
    {
        return true;
    }
    return false;
}
