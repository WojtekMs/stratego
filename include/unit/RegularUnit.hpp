#pragma once

#include "unit/UnitCounter.hpp"
#include "unit/UnitModel.hpp"

enum class Turn;

class RegularUnit {
  UnitModel model_;
  RegularUnitCounter counter_;

public:
  explicit RegularUnit(int value, Turn player);
  int get_value() const noexcept { return model_.get_value(); }
  [[deprecated("Future refactoring will remove get_type()")]] std::string
  get_type() const noexcept {
    return model_.get_type();
  }
  Turn get_owner() const noexcept { return model_.get_owner(); }
  static int get_count(int value) { RegularUnitCounter::get_count(value); }
  static int get_max_count(int value) {
    RegularUnitCounter::get_max_count(value);
  }
};
