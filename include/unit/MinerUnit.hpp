#pragma once

#include "unit/UnitModel.hpp"
#include "unit/UnitCounter.hpp"

namespace details {
constexpr const int maxMinerCount{4};
}


enum class Turn;
class MinerUnit
{
    UnitModel model_;
    UnitCounter<struct MinerTag, details::maxMinerCount> counter_;
public:
    explicit MinerUnit(Turn player);
    int get_value() const noexcept { return model_.get_value(); }
    [[deprecated("Future refactoring will remove get_type()")]] std::string get_type() const noexcept { return model_.get_type(); }
    Turn get_owner() const noexcept { return model_.get_owner(); }
    static int get_count() { return UnitCounter<MinerUnit, details::maxMinerCount>::get_count(); }
    static int get_max_count() { return UnitCounter<MinerUnit, details::maxMinerCount>::get_max_count(); }
};
