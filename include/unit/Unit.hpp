#pragma once

#include <variant>

#include "unit/BombUnit.hpp"
#include "unit/FlagUnit.hpp"
#include "unit/MinerUnit.hpp"
#include "unit/RegularUnit.hpp"
#include "unit/ScoutUnit.hpp"
#include "unit/SpyUnit.hpp"

using Unit = std::variant<BombUnit, FlagUnit, MinerUnit, RegularUnit, ScoutUnit, SpyUnit>;

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };