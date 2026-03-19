#pragma once

#include <chrono>

namespace knapsack {

class ScopedTimer {
public:
    ScopedTimer() : start_(clock::now()) {}

    double elapsed_ms() const {
        const auto end = clock::now();
        return std::chrono::duration<double, std::milli>(end - start_).count();
    }

private:
    using clock = std::chrono::steady_clock;
    clock::time_point start_;
};

} // namespace knapsack
