#pragma once

#include "unit/UnitModel.hpp"
#include "unit/UnitCounter.hpp"

namespace details {
constexpr const int maxFlagCount{1};
}

enum class Turn;
class FlagUnit
{
    UnitModel model_;
    UnitCounter<struct FlagTag, details::maxFlagCount> counter_;
public:
    explicit FlagUnit(Turn player);
    int get_value() const noexcept { return model_.get_value(); }
    [[deprecated("Future refactoring will remove get_type()")]] std::string get_type() const noexcept { return model_.get_type(); }
    Turn get_owner() const noexcept { return model_.get_owner(); }
    static int get_count() { return UnitCounter<FlagUnit, details::maxFlagCount>::get_count(); }
    static int get_max_count() { return UnitCounter<FlagUnit, details::maxFlagCount>::get_max_count(); }
};