#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <codecvt>

void print_info(const std::wstring& line) {
    std::wcout << line << std::endl;
    std::wcout << "\tCharacter count: " << line.size() - 1 << std::endl;
    std::wcout << "\tWord count: " << std::count(line.begin(), line.end(), ' ') + 1 << std::endl;
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.utf-8");
    std::wifstream input_file("stroka_3.txt");
    input_file.imbue(std::locale(input_file.getloc(), new std::codecvt_utf8<wchar_t>));

    for (std::wstring line; std::getline(input_file, line); ) {
        print_info(line);
    }
    return 0;
}
