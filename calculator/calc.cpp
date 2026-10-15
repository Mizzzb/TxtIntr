#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

void printUsage() {
    std::cout << "Калькулятор (мультипликативный, вариант 3)\n"
              << "Использование:\n"
              << "  ./calc -o multiply  A B [C [D]]   — умножение всех операндов\n"
              << "  ./calc -o divide    A B [C [D]]   — деление A на B, C, D\n"
              << "  ./calc --operation multiply ...\n"
              << "  ./calc --operation divide   ...\n"
              << "  ./calc -h | --help                — эта справка\n\n"
              << "Операндов от 2 до 4. Пример:\n"
              << "  ./calc -o multiply 2 3 4\n"
              << "  ./calc -o divide 100 2 5\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            printUsage();
            return 0;
        }
    }

    std::string operation;
    std::vector<double> operands;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-o") == 0 || std::strcmp(argv[i], "--operation") == 0) {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: не указано имя операции после " << argv[i] << "\n";
                printUsage();
                return 1;
            }
            operation = argv[++i];
        } else {
            char* end = nullptr;
            double val = std::strtod(argv[i], &end);
            if (end == argv[i] || *end != '\0') {
                std::cerr << "Ошибка: '" << argv[i] << "' не является числом\n";
                return 1;
            }
            operands.push_back(val);
        }
    }

    if (operation.empty()) {
        std::cerr << "Ошибка: не указана операция (-o multiply | -o divide)\n\n";
        printUsage();
        return 1;
    }

    if (operands.size() < 2 || operands.size() > 4) {
        std::cerr << "Ошибка: нужно от 2 до 4 операндов, получено " << operands.size() << "\n\n";
        printUsage();
        return 1;
    }

    if (operation == "multiply" || operation == "mul" || operation == "умножение") {
        double result = 1.0;
        for (double v : operands) result *= v;
        std::cout << result << "\n";
    }
    else if (operation == "divide" || operation == "div" || operation == "деление") {
        double result = operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            if (operands[i] == 0.0) {
                std::cerr << "Ошибка: деление на ноль (операнд №" << (i + 1) << ")\n";
                return 1;
            }
            result /= operands[i];
        }
        std::cout << result << "\n";
    }
    else {
        std::cerr << "Ошибка: неизвестная операция '" << operation << "'\n\n";
        printUsage();
        return 1;
    }

    return 0;
}
