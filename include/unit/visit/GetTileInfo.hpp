#pragma once

#include <optional>
#include <string>

#include "Turn.hpp"
#include "unit/UnitConcepts.hpp"

class GetTileInfo {
private:
  Turn player_;

public:
  explicit GetTileInfo(Turn player) : player_(player) {}

  template <unit::Owned UnitType> std::string operator()(const UnitType &unit) {
    if (unit.get_owner() != player_) {
      return "enemy";
    } else {
      return unit.get_type();
    }
  }
};