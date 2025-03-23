#pragma once

#include "unit/UnitCounter.hpp"

#include <iostream>
#include <unordered_map>

#include "unit/RegularUnit.hpp"

std::unordered_map<int, int> RegularUnitCounter::count_ = {};

struct RegularUnitMaxCount {
  int operator()(int unit_value) {
    switch (unit_value) {
    case 4:
    case 5:
    case 6:
      return 4;
    case 7:
      return 3;
    case 8:
      return 2;
    case 9:
      return 1;
    case 10:
      return 1;
    default:
      break;
    }
    std::cerr << "Unexpected unit value: " << unit_value
              << ", returning max count 0\n";
    return 0;
  }
};

RegularUnitCounter::RegularUnitCounter(const int unit_value)
    : unit_value_(unit_value) {
  ++count_[unit_value];
}
RegularUnitCounter::RegularUnitCounter(const RegularUnitCounter &rhs)
    : RegularUnitCounter(rhs.unit_value_) {}
RegularUnitCounter &
RegularUnitCounter::operator=(const RegularUnitCounter &rhs) {
  if (this != &rhs) {
    unit_value_ = rhs.unit_value_;
    ++count_[unit_value_];
  }
  return *this;
};
RegularUnitCounter::RegularUnitCounter(RegularUnitCounter &&) = default;
RegularUnitCounter &
RegularUnitCounter::operator=(RegularUnitCounter &&) = default;
RegularUnitCounter::~RegularUnitCounter() { --count_[unit_value_]; }

int RegularUnitCounter::get_count(const int value) { return count_[value]; }
int RegularUnitCounter::get_max_count(const int value) {
  return RegularUnitMaxCount{}(value);
}