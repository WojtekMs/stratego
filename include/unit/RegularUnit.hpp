#pragma once

#include "unit/Unit.hpp"

enum class Turn;
class RegularUnit : public Unit {
public:
    explicit RegularUnit(int value, Turn player);
};
