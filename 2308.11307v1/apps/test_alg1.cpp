#include <cstdlib>
#include <iostream>

#include "common/random_instance.hpp"
#include "solvers/alg1_interval_dp.hpp"
#include "solvers/zero_one_dp.hpp"

int main(int argc, char** argv) {
    int trials = 200;
    int n = 30;
    int w_max = 20;
    int v_max = 50;
    double capacity_ratio = 0.5;
    double delta_factor = 6.0;

    if (argc >= 2) trials = std::atoi(argv[1]);
    if (argc >= 3) n = std::atoi(argv[2]);
    if (argc >= 4) w_max = std::atoi(argv[3]);
    if (argc >= 5) v_max = std::atoi(argv[4]);
    if (argc >= 6) capacity_ratio = std::atof(argv[5]);
    if (argc >= 7) delta_factor = std::atof(argv[6]);

    int mismatches = 0;
    for (int t = 0; t < trials; ++t) {
        const auto inst = knapsack::generate_random_instance_01(
            n, w_max, v_max, capacity_ratio, static_cast<std::uint64_t>(t + 1));

        const auto exact = knapsack::solve_zero_one_dp_exact(inst.items, inst.capacity);
        const auto alg1 = knapsack::solve_alg1_interval_dp(
            inst.items,
            inst.capacity,
            knapsack::Alg1Params{.seed = static_cast<std::uint64_t>(t + 123456), .delta_factor = delta_factor}
        );

        if (exact.best_value != alg1.best_value) {
            ++mismatches;
            std::cout << "[Mismatch] trial=" << t
                      << " exact=" << exact.best_value
                      << " alg1=" << alg1.best_value
                      << " capacity=" << inst.capacity
                      << " n=" << n
                      << " w_max=" << w_max
                      << "\n";
        }
    }

    std::cout << "Trials: " << trials << "\n";
    std::cout << "Mismatches: " << mismatches << "\n";
    std::cout << "Match rate: " << (100.0 * static_cast<double>(trials - mismatches) / static_cast<double>(trials)) << "%\n";
    return 0;
}
