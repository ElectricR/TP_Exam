#include <iostream>
#include <string>
#include <fstream>
#include <codecvt>
#include <regex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>
#include <iomanip>

auto get_range(std::vector<unsigned>& refs) {
    return  std::ranges::views::iota(static_cast<size_t>(0), refs.size()) | std::ranges::views::transform([&refs](const size_t i) -> std::wstring { 
            std::wstringstream ss;
            ss << std::left << std::setw(8) << std::to_wstring(i + 1) + L'.' << std::right;
            ss << L'[' << std::setfill(L'0') << std::setw(2) << refs[i] << L']';
            return ss.str();
            });
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.utf-8");
    std::wifstream input_file("Tstatja.txt");
    input_file.imbue(std::locale(input_file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstring text;
    unsigned line_count = 0;
    for (std::wstring line; std::getline(input_file, line);) {
        text += line;
        ++line_count;
    }
    std::wcout << "Line count: " << line_count << std::endl << std::endl;
    std::wcout << "Text: " << std::endl << std::endl << text << std::endl << std::endl;

    std::vector<unsigned> refs;
    std::wregex ref_pattern(L"\\[(\\d+)\\]");
    for (auto it = std::wsregex_iterator(text.begin(), text.end(), ref_pattern); it != std::wsregex_iterator(); ++it) {
        refs.emplace_back(std::stoul((*it)[1]));
    }

    std::wcout << "Cited sources:" << std::endl;
    std::ranges::copy(get_range(refs).begin(), get_range(refs).end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    std::wcout << std::endl;
    std::ranges::sort(refs);
    std::wcout << "Sorted cited sources:" << std::endl;
    std::ranges::copy(get_range(refs).begin(), get_range(refs).end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    auto last = std::unique(refs.begin(), refs.end());
    refs.erase(last, refs.end());
    std::wcout << std::endl;
    std::wcout << "Unique sorted cited sources:" << std::endl;
    std::ranges::copy(get_range(refs).begin(), get_range(refs).end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    
    return 0;
}



