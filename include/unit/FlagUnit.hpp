#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class FlagUnit : public Unit {
public:
    FlagUnit(Turn player)
        : Unit(-1, "flag", player, false){};
    virtual ~FlagUnit(){};
};