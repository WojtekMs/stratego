#pragma once

#include "Unit.hpp"

enum class TURN;
class FlagUnit : public Unit {
public:
    FlagUnit(TURN player)
        : Unit(-1, "flag", player, false){};
    virtual ~FlagUnit(){};
};