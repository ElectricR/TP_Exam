#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <codecvt>

int main() {
    std::setlocale(LC_ALL, "ru_RU.utf-8");
    std::wifstream input_file("Sintax.txt");
    input_file.imbue(std::locale(input_file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstring line;
    std::getline(input_file, line);
    
    std::wregex sentence_regex(L"[^ ][^.?!]*[.!?]");

    for (std::wsregex_iterator it = std::wsregex_iterator(line.begin(), line.end(), sentence_regex); it != std::wsregex_iterator(); ++it) {
        std::wregex punct(L" *([!.?,;:-]) *");
        auto sentence = std::regex_replace((*it).str(), punct, L"$1 ");
        sentence[0] = std::toupper(sentence[0]);
        std::wcout << sentence << std::endl;
    }

    return 0;
}
