#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class MinerUnit : public Unit
{
public:
    explicit MinerUnit(Turn player);
};
