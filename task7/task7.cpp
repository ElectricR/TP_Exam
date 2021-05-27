#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <codecvt>
#include <vector>
#include <sstream>
#include <numeric>
#include <utility>
#include <algorithm>
#include <iomanip>

struct student {
    std::wstring group;
    std::vector<std::wstring> name;
    std::vector<double> grades;
    double sum;

    bool operator<(const student& o) {
        return name < o.name;
    }
};

void print_header(std::wostream& o) {
    o << "Group\t" << std::left << std::setw(40) << "Name" << "Lb1\tLb2\tLb3\tLb4\tLb5\tLb6\tSum" << std::endl << std::right;
    o << std::setfill(L'-') << std::setw(100) << L'-' << std::setfill(L' ') << std::endl;
}

void print_debt_header(std::wostream& o) {
    o << "Group\t" << std::left << std::setw(40) << "Name" << "Debt" << std::endl << std::right;
    o << std::setfill(L'-') << std::setw(70) << L'-' << std::setfill(L' ') << std::endl;
}

std::wstring print_student(const student& st) { 
    std::wstringstream stream;
    stream << st.group << L"\t";
    stream << std::setw(40) << std::left << st.name[0] + L' ' + st.name[1] + L' ' + st.name[2] << std::right;
    for (auto i : std::ranges::views::iota(0, 6)) {
        stream << st.grades[i] << L"\t";
    }
    stream << st.sum;
    return stream.str();
}

double calc_debt(const student& st) {
    if (st.sum >= 100) {
        if (std::all_of(st.grades.begin(), st.grades.end(), [](const double gr) { return gr >= 0; })) {
            return 0;
        }
        else {
            auto grrange = st.grades | std::ranges::views::filter([](const double gr) { return gr < 0; });
            return std::accumulate(grrange.begin(), grrange.end(), 0);
        }
    }
    else {
        return 100 - st.sum;
    }
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wifstream input_file("spisok-2020.txt");
    input_file.imbue(std::locale(input_file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::vector<student> students;
    for (std::wstring line; std::getline(input_file, line);) {
        std::wstringstream linestream(line);
        std::wstring group;
        linestream >> group;
        std::vector<std::wstring> name;
        std::copy_n(std::istream_iterator<std::wstring, wchar_t>(linestream), 3, std::back_inserter(name));
        std::vector<double> grades;
        std::copy_n(std::istream_iterator<double, wchar_t>(linestream), 6, std::back_inserter(grades));
        double sum;
        linestream >> sum;
        students.emplace_back(std::move(group), std::move(name), std::move(grades), sum);
    }

    // Task7.1
    std::wcout << "Number of students: " << students.size() << std::endl << std::endl;
    print_header(std::wcout);
    auto frange = students | std::ranges::views::transform(print_student);
    std::ranges::copy(frange.begin(), frange.end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    //Task 7.2
    std::sort(students.begin(), students.end());
    std::wcout << std::endl << "Enter group name" << std::endl;
    std::wstring task2_group;
    std::wcin >> task2_group;
    auto drange = students | std::ranges::views::filter([&task2_group](const student& st) { return st.group == task2_group; }) | std::ranges::views::transform(print_student);
    std::wcout << L"Список студентов группы " << task2_group << std::endl << std::endl;
    print_header(std::wcout);
    std::ranges::copy(drange.begin(), drange.end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    //Task 7.3
    auto trange = students | std::ranges::views::filter([&task2_group](const student& st) { return st.group == task2_group; }) | 
        std::ranges::views::filter([](const student& st) { 
                return st.sum >= 100 && 
                std::all_of(st.grades.begin(), st.grades.end(), 
                        [](const double gr) { return gr >= 0; }
                        ); 
                }) | 
        std::ranges::views::transform(print_student);
    std::wcout << std::endl;
    std::wcout << L"Список студентов, имеющих право на досрочный зачет" << std::endl << std::endl;
    print_header(std::wcout);
    std::ranges::copy(trange.begin(), trange.end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));
    
    //Task 7.4
    auto fourth_range = students | std::ranges::views::filter([&task2_group](const student& st) { return st.group == task2_group; }) | std::ranges::views::transform([](const student& st) { 
            std::wstringstream stream;
            stream  << st.group << L"\t";
            stream << std::setw(40) << std::left << st.name[0] + L' ' + st.name[1] + L' ' + st.name[2] << calc_debt(st) << std::right;
            return stream.str();
            });
    std::wcout << L'\n';
    std::wcout << L"Сумма долга на зачет у студентов группы " << task2_group << std::endl << std::endl;
    print_debt_header(std::wcout);
    std::ranges::copy(fourth_range.begin(), fourth_range.end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));
    
    //Task 7.5
    std::wcout << std::endl << "Enter student surname" << std::endl;
    std::wstring task5_name;
    std::wcin >> task5_name;
    std::wcout << L'\n';
    auto lower = std::ranges::lower_bound(students, task5_name, {}, [](const student& st) { return st.name[0]; });
    auto upper = std::ranges::upper_bound(students, task5_name, {}, [](const student& st) { return st.name[0]; });
    auto fifth_range = std::ranges::subrange(lower, upper) | std::ranges::views::transform(print_student);
    std::wcout << L"Поиск данных по фамилии" << std::endl << std::endl;
    print_header(std::wcout);
    std::ranges::copy(fifth_range.begin(), fifth_range.end(), std::ostream_iterator<std::wstring, wchar_t>(std::wcout, L"\n"));

    return 0;
    }

