#pragma once

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

#include "common/types.hpp"

namespace knapsack {

inline Instance01 generate_random_instance_01(
    int n,
    int w_max,
    int v_max,
    double capacity_ratio,
    std::uint64_t seed
) {
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> wdist(1, w_max);
    std::uniform_int_distribution<int> vdist(1, v_max);

    Instance01 inst;
    inst.items.reserve(n);
    inst.w_max = w_max;

    long long total_weight = 0;
    for (int i = 0; i < n; ++i) {
        const int w = wdist(rng);
        const long long v = vdist(rng);
        inst.items.push_back(Item01{.id = i, .weight = w, .value = v});
        total_weight += w;
    }

    long long cap = static_cast<long long>(capacity_ratio * static_cast<double>(total_weight));
    cap = std::clamp<long long>(cap, 1, total_weight);
    inst.capacity = static_cast<int>(cap);
    return inst;
}

} // namespace knapsack
