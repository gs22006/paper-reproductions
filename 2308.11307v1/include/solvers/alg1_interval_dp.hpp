#pragma once

#include <vector>

#include "common/types.hpp"

namespace knapsack {

SolveResult solve_alg1_interval_dp(
    const std::vector<Item01>& items,
    int capacity,
    const Alg1Params& params
);

} // namespace knapsack
