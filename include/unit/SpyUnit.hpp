#pragma once

#include "unit/UnitCounter.hpp"
#include "unit/UnitModel.hpp"

namespace details {
constexpr const int maxSpyCount{1};
}

enum class Turn;

class SpyUnit {
  UnitModel model_;
  UnitCounter<struct SpyTag, details::maxSpyCount> counter_;

public:
  explicit SpyUnit(Turn player);
  int get_value() const noexcept { return model_.get_value(); }
  [[deprecated("Future refactoring will remove get_type()")]] std::string
  get_type() const noexcept {
    return model_.get_type();
  }
  Turn get_owner() const noexcept { return model_.get_owner(); }
  static int get_count() {
    return UnitCounter<SpyUnit, details::maxSpyCount>::get_count();
  }
  static int get_max_count() {
    return UnitCounter<SpyUnit, details::maxSpyCount>::get_max_count();
  }
};
