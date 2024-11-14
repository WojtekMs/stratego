#include "unit/Movable.hpp"

#include "unit/Unit.hpp"
#include "Tile.hpp"

Movable::Movable(Movable::Delegate* del) : delegate(del) {}

bool Movable::can_move(int from_x, int from_y, int to_x, int to_y) const
{
    if (from_x + 1 == to_x && from_y == to_y) {
        return true;
    }
    if (from_x - 1 == to_x && from_y == to_y) {
        return true;
    }
    if (from_x == to_x && from_y + 1 == to_y) {
        return true;
    }
    if (from_x == to_x && from_y - 1 == to_y) {
        return true;
    }
    return false;
}

Result Movable::attack(const std::shared_ptr<Unit>& rhs) const
{
    if (!rhs) {
        throw std::invalid_argument(
            "Movable.cpp:27 - unit you try to attack doesn't exist");
    }
    if (rhs->get_type() == "bomb") {
        return Result::Lost;
    }
    if (delegate->get_value() > rhs->get_value()) {
        return Result::Won;
    }
    if (delegate->get_value() == rhs->get_value()) {
        return Result::Draw;
    }
    return Result::Lost;
}
