#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common/csv.hpp"
#include "common/random_instance.hpp"
#include "solvers/alg1_interval_dp.hpp"
#include "solvers/zero_one_dp.hpp"

namespace fs = std::filesystem;

static double median(std::vector<double> xs) {
    std::sort(xs.begin(), xs.end());
    const std::size_t m = xs.size() / 2;
    if (xs.size() % 2 == 1) return xs[m];
    return 0.5 * (xs[m - 1] + xs[m]);
}

int main(int argc, char** argv) {
    std::string mode = "by_n";
    std::string output = "data/alg1_benchmark.csv";
    int trials = 5;
    double delta_factor = 6.0;

    if (argc >= 2) mode = argv[1];
    if (argc >= 3) output = argv[2];
    if (argc >= 4) trials = std::atoi(argv[3]);
    if (argc >= 5) delta_factor = std::atof(argv[4]);

    fs::create_directories(fs::path(output).parent_path());
    std::ofstream out(output);
    knapsack::write_csv_row(out, {
        "experiment","algo","seed","n","w_max","v_max","capacity","trial","time_ms","best_value","correct"
    });

    if (mode == "by_n") {
        const int w_max = 100;
        const int v_max = 1000;
        const double capacity_ratio = 0.35;
        const std::vector<int> ns = {200, 400, 800, 1200, 1600, 2000};

        for (int n : ns) {
            for (int t = 0; t < trials; ++t) {
                const std::uint64_t seed = 100000ULL + 1000ULL * static_cast<std::uint64_t>(n) + static_cast<std::uint64_t>(t);
                const auto inst = knapsack::generate_random_instance_01(n, w_max, v_max, capacity_ratio, seed);
                const auto exact = knapsack::solve_zero_one_dp_exact(inst.items, inst.capacity);
                const auto alg1 = knapsack::solve_alg1_interval_dp(inst.items, inst.capacity, {.seed = seed + 7, .delta_factor = delta_factor});

                knapsack::write_csv_row(out, {
                    mode, "baseline_dp", std::to_string(seed), std::to_string(n), std::to_string(w_max), std::to_string(v_max),
                    std::to_string(inst.capacity), std::to_string(t), std::to_string(exact.elapsed_ms), std::to_string(exact.best_value), "1"
                });
                knapsack::write_csv_row(out, {
                    mode, "alg1", std::to_string(seed), std::to_string(n), std::to_string(w_max), std::to_string(v_max),
                    std::to_string(inst.capacity), std::to_string(t), std::to_string(alg1.elapsed_ms), std::to_string(alg1.best_value),
                    (alg1.best_value == exact.best_value ? "1" : "0")
                });
            }
        }
    } else if (mode == "by_wmax") {
        const int n = 1500;
        const int v_max = 1000;
        const double capacity_ratio = 0.35;
        const std::vector<int> wmaxs = {20, 40, 80, 120, 160, 200};

        for (int w_max : wmaxs) {
            for (int t = 0; t < trials; ++t) {
                const std::uint64_t seed = 200000ULL + 1000ULL * static_cast<std::uint64_t>(w_max) + static_cast<std::uint64_t>(t);
                const auto inst = knapsack::generate_random_instance_01(n, w_max, v_max, capacity_ratio, seed);
                const auto exact = knapsack::solve_zero_one_dp_exact(inst.items, inst.capacity);
                const auto alg1 = knapsack::solve_alg1_interval_dp(inst.items, inst.capacity, {.seed = seed + 7, .delta_factor = delta_factor});

                knapsack::write_csv_row(out, {
                    mode, "baseline_dp", std::to_string(seed), std::to_string(n), std::to_string(w_max), std::to_string(v_max),
                    std::to_string(inst.capacity), std::to_string(t), std::to_string(exact.elapsed_ms), std::to_string(exact.best_value), "1"
                });
                knapsack::write_csv_row(out, {
                    mode, "alg1", std::to_string(seed), std::to_string(n), std::to_string(w_max), std::to_string(v_max),
                    std::to_string(inst.capacity), std::to_string(t), std::to_string(alg1.elapsed_ms), std::to_string(alg1.best_value),
                    (alg1.best_value == exact.best_value ? "1" : "0")
                });
            }
        }
    } else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    std::cout << "Wrote benchmark CSV to: " << output << "\n";
    return 0;
}
