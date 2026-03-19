#pragma once

#include <vector>

#include "common/types.hpp"

namespace knapsack {

SolveResult solve_zero_one_dp_exact(
    const std::vector<Item01>& items,
    int capacity
);

} // namespace knapsack
