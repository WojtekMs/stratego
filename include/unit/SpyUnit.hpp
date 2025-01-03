#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class SpyUnit : public Unit {
public:
    SpyUnit(Turn player);
};
