#include <iostream>
#include <ranges>
#include <vector>
#include <numeric>
#include <algorithm>

bool check(const std::vector<unsigned>& vec) {
    auto range_vec = std::ranges::views::iota(0, 9) | std::ranges::views::transform([&vec](const int i) { return vec[i]; });
    return std::ranges::is_permutation(std::ranges::views::iota(1, 10), range_vec);
}
            
int main() {
    std::vector<std::vector<unsigned>> matrix;
    for (auto i : std::ranges::views::iota(0, 9)) {
        matrix.push_back({});
        std::copy_n(std::istream_iterator<unsigned>(std::cin), 9, std::back_inserter(matrix[i]));
    }
    for (auto i : std::ranges::views::iota(0, 9)) {
        auto col_range = std::ranges::views::iota(0, 9) | std::ranges::views::transform([&matrix, &i](const int j) { return matrix[i][j]; });
        auto quad_range = std::ranges::views::iota(0, 9) | std::ranges::views::transform([&matrix, &i](const int j) { return matrix[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3]; });
        if (!check(matrix[i]) || !check({col_range.begin(), col_range.end()}) || !check({quad_range.begin(), quad_range.end()})) {
            std::cout << "Not sudoku" << std::endl;
            return 0;
        }
    }
    std::cout << "It is sudoku" << std::endl;
    return 0;
}



