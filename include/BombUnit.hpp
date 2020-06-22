#pragma once

#include "Unit.hpp"

enum class TURN;
class BombUnit : public Unit {
public:
    BombUnit(TURN player)
        : Unit(0, "bomb", player, false){};
    virtual ~BombUnit(){};
};
