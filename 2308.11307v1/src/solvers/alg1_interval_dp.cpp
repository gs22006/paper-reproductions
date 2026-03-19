#include "solvers/alg1_interval_dp.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

#include "common/timer.hpp"

namespace knapsack {

namespace {

struct Interval {
    int left{};
    int right{};
};

Interval build_interval(int i, int n, int capacity, int w_max, double delta_factor) {
    const double log_term = std::max(1.0, std::log(static_cast<double>(std::max(2, n))));
    const double mu = static_cast<double>(i) * static_cast<double>(capacity) / static_cast<double>(n);
    const double delta = delta_factor * static_cast<double>(w_max) * std::sqrt(static_cast<double>(i) * log_term);

    int left = static_cast<int>(std::floor(mu - delta));
    int right = static_cast<int>(std::ceil(mu + delta));
    left = std::max(left, 0);
    right = std::min(right, capacity);
    if (left > right) {
        left = right = std::clamp(static_cast<int>(std::round(mu)), 0, capacity);
    }
    return Interval{left, right};
}

} // namespace

SolveResult solve_alg1_interval_dp(
    const std::vector<Item01>& items,
    int capacity,
    const Alg1Params& params
) {
    ScopedTimer timer;

    if (items.empty() || capacity <= 0) {
        return SolveResult{.best_value = 0, .used_weight = 0, .elapsed_ms = timer.elapsed_ms()};
    }

    std::vector<Item01> permuted = items;
    std::mt19937_64 rng(params.seed);
    std::shuffle(permuted.begin(), permuted.end(), rng);

    const int n = static_cast<int>(permuted.size());
    int w_max = 0;
    for (const auto& item : permuted) {
        w_max = std::max(w_max, item.weight);
    }

    constexpr long long NEG_INF = std::numeric_limits<long long>::min() / 4;

    Interval prev_interval{0, 0};
    std::vector<long long> prev(1, 0);

    for (int i = 1; i <= n; ++i) {
        const auto& item = permuted[i - 1];
        const Interval cur_interval = build_interval(i, n, capacity, w_max, params.delta_factor);
        std::vector<long long> cur(cur_interval.right - cur_interval.left + 1, NEG_INF);

        for (int w = cur_interval.left; w <= cur_interval.right; ++w) {
            long long best = NEG_INF;

            if (w >= prev_interval.left && w <= prev_interval.right) {
                best = std::max(best, prev[w - prev_interval.left]);
            }

            const int prev_w = w - item.weight;
            if (prev_w >= prev_interval.left && prev_w <= prev_interval.right) {
                const long long cand = prev[prev_w - prev_interval.left];
                if (cand != NEG_INF) {
                    best = std::max(best, cand + item.value);
                }
            }

            cur[w - cur_interval.left] = best;
        }

        prev_interval = cur_interval;
        prev.swap(cur);
    }

    long long best_value = 0;
    int best_weight = 0;
    for (int w = prev_interval.left; w <= prev_interval.right; ++w) {
        const long long val = prev[w - prev_interval.left];
        if (val > best_value) {
            best_value = val;
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
