#pragma once

#include <cstdint>
#include <vector>

namespace knapsack {

struct Item01 {
    int id{};
    int weight{};
    long long value{};
};

struct SolveResult {
    long long best_value{};
    int used_weight{};
    double elapsed_ms{};
    bool exact_match_known{false};
    bool exact_match{false};
};

struct Alg1Params {
    std::uint64_t seed{1};
    double delta_factor{6.0};
};

struct Instance01 {
    std::vector<Item01> items;
    int capacity{};
    int w_max{};
};

} // namespace knapsack
