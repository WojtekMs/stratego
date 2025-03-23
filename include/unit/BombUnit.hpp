#pragma once

#include "unit/UnitModel.hpp"
#include "unit/UnitCounter.hpp"

namespace details {
constexpr const int maxBombCount{6};
}

enum class Turn;
class BombUnit {
    UnitModel model_;
    UnitCounter<struct BombTag, details::maxBombCount> counter_;
public:
    explicit BombUnit(Turn player);
    int get_value() const noexcept { return model_.get_value(); }
    [[deprecated("Future refactoring will remove get_type()")]] std::string get_type() const noexcept { return model_.get_type(); }
    Turn get_owner() const noexcept { return model_.get_owner(); }
    static int get_count() { return UnitCounter<BombUnit, details::maxBombCount>::get_count(); }
    static int get_max_count() { return UnitCounter<BombUnit, details::maxBombCount>::get_max_count(); }
};
