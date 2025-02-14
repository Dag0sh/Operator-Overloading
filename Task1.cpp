#include <stdio.h>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

bool hasInvalidCharacters(const char* str) {
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-') {
            return true;  // Найден недопустимый символ
        }
    }
    return false;  // Все символы допустимы
}

bool hasOnlyDigits(const char* str) {
    bool hasDecimalPoint = false;
    size_t startIndex = 0;

    // Разрешаем первый символ быть '-' для отрицательных чисел
    if (str[0] == '-') {
        startIndex = 1;
    }

    for (size_t i = startIndex; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            // Разрешаем только одну точку в числе
            if (str[i] == '.' && !hasDecimalPoint) {
                hasDecimalPoint = true;
            } else {
                return false;  // Любой другой символ недопустим
            }
        }
    }
    return true;
}

class Double {
   private:
    double value;

   public:
    Double(double val) : value(val) {}

    Double& operator++() {
        value++;
        return *this;
    }

    friend Double& operator--(Double& val);

    double getValue() const { return value; }
};

Double& operator--(Double& val) {
    val.value--;
    return val;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double vall;
    int ch;
    char s[2];
    char input[8];
    std::cout << std::defaultfloat;
    std::cout.precision(6);

    do {
        std::cout << "Исходное значение: ";
        // Проверка на корректный ввод типа double
        while (true) {
            cin.getline(input, sizeof(input));
            vall = atof(input);
            if (vall > 1000 || vall < -1000 || strlen(input) > 7 || !hasOnlyDigits(input) ||
                hasInvalidCharacters(input)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод! Попробуйте снова." << endl;
            } else {
                vall = atof(input);
                break;
            }
        }

        Double num(vall);
        // Использование оператора инкремента (++)
        ++num;
        std::cout << "Значение после использования инкремента: " << num.getValue() << std::endl;

        num = vall;  // Сброс значения num до начального
        // Использование оператора декремента (--)
        --num;
        std::cout << "Значение после использования декремента: " << num.getValue() << std::endl;

        std::cout << "\n1 - если хотите начать заново\
                                \n2 - выход;\n";

        do {
            cout << "Введите либо 1, либо 2\n";
            cin >> s;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ch = atoi(s);
        } while (ch != 1 && ch != 2);

        switch (ch) {
            case 1:
                continue;
            case 2:
                return 0;
        }
    } while (true);

    return 0;
}