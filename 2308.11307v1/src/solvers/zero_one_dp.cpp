#include "solvers/zero_one_dp.hpp"

#include <algorithm>
#include <limits>
#include <vector>

#include "common/timer.hpp"

namespace knapsack {

SolveResult solve_zero_one_dp_exact(
    const std::vector<Item01>& items,
    int capacity
) {
    ScopedTimer timer;

    constexpr long long NEG_INF = std::numeric_limits<long long>::min() / 4;
    std::vector<long long> dp(capacity + 1, NEG_INF);
    dp[0] = 0;

    for (const auto& item : items) {
        for (int w = capacity; w >= item.weight; --w) {
            if (dp[w - item.weight] == NEG_INF) continue;
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    long long best_value = 0;
    int best_weight = 0;
    for (int w = 0; w <= capacity; ++w) {
        if (dp[w] > best_value) {
            best_value = dp[w];
            best_weight = w;
        }
    }

    return SolveResult{
        .best_value = best_value,
        .used_weight = best_weight,
        .elapsed_ms = timer.elapsed_ms(),
        .exact_match_known = false,
        .exact_match = false,
    };
}

} // namespace knapsack
