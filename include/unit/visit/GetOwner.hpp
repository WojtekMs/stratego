#pragma once

#include "unit/UnitConcepts.hpp"

enum class Turn;
class GetOwner {
public:
  template <unit::Owned T> Turn operator()(const T &unit) {
    return unit.get_owner();
  }
};