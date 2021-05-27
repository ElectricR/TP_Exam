#include <iostream>

int main() {
    double temp = 0.0;
    double current = 0.0;
    char op = 0;
    std::cin >> temp;
    while (true) {
        std::cin >> op;
        switch (op) {
            case 'C': {
                temp = 0.0;
                std::cin >> temp;
                break;
            }
            case 'Q': {
                std::cout << temp << std::endl;
                return 0;
            }
            default: {
                std::cin >> current;
                switch (op) {
                    case '+': {
                        temp += current;
                        break;
                    }
                    case '*': {
                        temp *= current;
                        break;
                    }
                    case '-': {
                        temp -= current;
                        break;
                    }
                    case '/': {
                        temp /= current;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            std::cout << temp << std::endl;
            }
        }
    }
}
