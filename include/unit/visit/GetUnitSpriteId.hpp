#pragma once 


#include "unit/Unit.hpp"

class GetUnitSpriteId {
public:
    int operator()(const RegularUnit& unit) {
        return unit.get_value() - 2;
    }
    int operator()(const ScoutUnit&) {
        return 0;
    }
    int operator()(const MinerUnit&) {
        return 1;
    }
    int operator()(const BombUnit&) {
        return 9;
    }
    int operator()(const FlagUnit&) {
        return 10;
    }
    int operator()(const SpyUnit&) {
        return 11;
    }
};