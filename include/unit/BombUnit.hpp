#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class BombUnit : public Unit {
public:
    BombUnit(Turn player)
        : Unit(0, "bomb", player, false){};
    virtual ~BombUnit(){};
};
