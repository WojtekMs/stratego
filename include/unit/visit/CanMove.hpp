#pragma once 

#include <string>
#include <variant>
#include <optional>

#include "Tile.hpp"
#include "unit/Unit.hpp"

class CanMove {
private:
    Tile from_{};
    Tile to_{};

    bool regularMove() const {
        if (from_.x + 1 == to_.x && from_.y == to_.y)
        {
            return true;
        }
        if (from_.x - 1 == to_.x && from_.y == to_.y)
        {
            return true;
        }
        if (from_.x == to_.x && from_.y + 1 == to_.y)
        {
            return true;
        }
        if (from_.x == to_.x && from_.y - 1 == to_.y)
        {
            return true;
        }
        return false;
    }

    bool scoutMove() const {
        if (from_.x == to_.x)
        {
            return true;
        }
        if (from_.y == to_.y)
        {
            return true;
        }
        return false;
    }

public:
    CanMove(Tile from, Tile to) : from_(from), to_(to) {}

    bool operator()(const ScoutUnit&) {
        return scoutMove();
    }
    bool operator()(const MinerUnit&) {
        return regularMove();
    }
    bool operator()(const RegularUnit&) {
        return regularMove();
    }
    bool operator()(const SpyUnit&) {
        return regularMove();
    }
    bool operator()(const FlagUnit&) {
        return false;
    }
    bool operator()(const BombUnit&) {
        return false;
    }
};