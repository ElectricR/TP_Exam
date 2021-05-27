#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>


bool check(const std::vector<unsigned>& vec, int target) {
    return std::accumulate(vec.begin(), vec.end(), 0) == target;
}
            
int main() {
    int size = 0;

    std::cout << "Please enter quad size" << std::endl;
    std::cin >> size;
    std::cout << "Please enter matrix" << std::endl;

    std::vector<std::vector<unsigned>> matrix;
    for (auto i : std::ranges::views::iota(0, size)) {
        matrix.push_back({});
        std::copy_n(std::istream_iterator<unsigned>(std::cin), size, std::back_inserter(matrix[i]));
    }

    int target = std::accumulate(matrix[0].begin(), matrix[0].end(), 0);
    for (auto i : std::ranges::views::iota(0, size)) {
        auto col_range = std::ranges::views::iota(0, size) | 
            std::ranges::views::transform([&matrix, &i](const int j) { 
                    return matrix[i][j]; 
                    });
        if (!check(matrix[i], target) || 
                !check({col_range.begin(), col_range.end()}, target)) {
            std::cout << "Not magical" << std::endl;
            return 0;
        }
    }

    auto main_diag_range = std::ranges::views::iota(0, size) | 
        std::ranges::views::transform([&matrix, &size](const int j) { 
                return matrix[j][j]; 
                });
    auto side_diag_range = std::ranges::views::iota(0, size) | 
        std::ranges::views::transform([&matrix, &size](const int j) { 
                return matrix[j][size - j - 1]; 
                });

    if (!check({main_diag_range.begin(), main_diag_range.end()}, target) || 
            !check({side_diag_range.begin(), side_diag_range.end()}, target)) {
        std::cout << "Not magical" << std::endl;
        return 0;
    }

    std::cout << "It is magical" << std::endl;
    return 0;
}




