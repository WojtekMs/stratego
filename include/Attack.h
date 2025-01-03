#pragma once

#include "unit/Unit.hpp"
#include "unit/MinerUnit.hpp"
#include "unit/BombUnit.hpp"
#include "unit/SpyUnit.hpp"
#include "unit/RegularUnit.hpp"

namespace attack
{
    enum class Result
    {
        Lost,
        Draw,
        Won,
    };
    std::string toString(Result result);

    void validateUnits(const std::shared_ptr<Unit> &lhs, const std::shared_ptr<Unit> &rhs);
    // This function is the actual strategy used by Board/Player
    Result attack(const std::shared_ptr<Unit> &lhs, const std::shared_ptr<Unit> &rhs);
}
