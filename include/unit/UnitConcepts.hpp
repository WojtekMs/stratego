#pragma once

#include <concepts>

#include "Turn.hpp"

namespace unit {
template <typename UnitType>
concept Attackable = requires(UnitType unit) {
  { unit.get_value() } -> std::same_as<int>;
};

template <typename UnitType>
concept Owned = requires(const UnitType &unit) {
  { unit.get_owner() } -> std::same_as<Turn>;
};
} // namespace unit