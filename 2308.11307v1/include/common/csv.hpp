#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace knapsack {

inline void write_csv_row(std::ofstream& out, const std::vector<std::string>& cols) {
    for (std::size_t i = 0; i < cols.size(); ++i) {
        if (i) out << ',';
        out << cols[i];
    }
    out << '\n';
}

} // namespace knapsack
