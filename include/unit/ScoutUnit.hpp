#pragma once

#include "unit/UnitCounter.hpp"
#include "unit/UnitModel.hpp"

namespace details {
constexpr const int maxScoutCount{8};
}

enum class Turn;
class ScoutUnit {
  UnitModel model_;
  UnitCounter<struct ScoutTag, details::maxScoutCount> counter_;

public:
  explicit ScoutUnit(Turn player);
  int get_value() const noexcept { return model_.get_value(); }
  [[deprecated("Future refactoring will remove get_type()")]] std::string
  get_type() const noexcept {
    return model_.get_type();
  }
  Turn get_owner() const noexcept { return model_.get_owner(); }
  static int get_count() {
    return UnitCounter<ScoutUnit, details::maxScoutCount>::get_count();
  }
  static int get_max_count() {
    return UnitCounter<ScoutUnit, details::maxScoutCount>::get_max_count();
  }
};