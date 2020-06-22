#include "Movable.hpp"
#include "Unit.hpp"

Movable::Movable(Movable::Delegate* del)
    : delegate(del) {
}

bool Movable::can_move(int from_x, int from_y, int to_x, int to_y) const {
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

RESULT Movable::attack(const std::shared_ptr<Unit>& rhs) const {
    if (rhs) {
        if (rhs->get_type() == "bomb") {
            return RESULT::LOST;
        }
        if (delegate->get_value() > rhs->get_value()) {
            return RESULT::WON;
        }
        if (delegate->get_value() == rhs->get_value()) {
            return RESULT::DRAW;
        }
        if (delegate->get_value() < rhs->get_value()) {
            return RESULT::LOST;
        }
    }
}