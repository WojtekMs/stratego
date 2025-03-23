#include "unit/RegularUnit.hpp"

RegularUnit::RegularUnit(int value, Turn player)
    : model_(value, "regular", player), counter_(value) {};
