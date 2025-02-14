#include <iostream>
#include <vector>

using namespace std;

class Stack {
   private:
    vector<int> elements;

   public:
    Stack() {}

    // Stack operator+(int num) {
    //     Stack newStack = *this;
    //     newStack.elements.push_back(num);
    //     return newStack;
    // }

    friend Stack operator*(const Stack& stack, int multiplier);

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    bool operator==(const Stack& other) const { return elements == other.elements; }

    bool operator!=(const Stack& other) const { return !(*this == other); }

    Stack& operator+=(int num) {
        elements.push_back(num);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Stack& stack);

    friend istream& operator>>(istream& is, Stack& stack);

    bool isEmpty() const { return elements.empty(); }
};

Stack operator*(const Stack& stack, int multiplier) {
    Stack newStack = stack;
    if (!newStack.elements.empty()) {
        newStack.elements.back() *= multiplier;
    }
    if (newStack.elements.back() > 10000) {
        newStack.elements.back() = 10000;
        return newStack;
    } else if (newStack.elements.back() < -10000) {
        newStack.elements.back() = -10000;
        return newStack;
    } else
        return newStack;
}

ostream& operator<<(ostream& os, const Stack& stack) {
    for (const int& element : stack.elements) {
        os << element << ' ';
    }
    return os;
}

istream& operator>>(istream& is, Stack& stack) {
    int num;
    while (is >> num) {
        stack.elements.push_back(num);
    }
    return is;
}

int main() {
    Stack stack1;
    Stack stack2;
    setlocale(LC_ALL, "Russian");
    int choice;
    int num;
    int mnoz;
    bool exit = false;

    while (!exit) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить элемент в первый стек" << endl;
        cout << "2. Выполнить умножение на верхний элемент первого стека" << endl;
        cout << "3. Вывести первый стек" << endl;
        cout << "4. Проверить, пуст ли первый стек" << endl;
        cout << "5. Присвоить второму стеку значение первого стека" << endl;
        cout << "6. Проверить равенство двух стеков" << endl;
        cout << "7. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите значение для добавления в первый стек: ";
                while (true) {
                    cin >> num;
                    if (cin.fail() || num <= -100 || num > 100 || cin.peek() != '\n') {
                        cout << "Некорректный ввод!" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    } else
                        break;
                }
                stack1 += num;
                break;
            case 2:
                if (!stack1.isEmpty()) {
                    cout << "Введите множитель: ";
                    cin >> mnoz;
                    if (cin.fail() || mnoz < -100 || mnoz > 100 || cin.peek() != '\n') {
                        cout << "Некорректный ввод!" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    stack1 = stack1 * mnoz;
                } else {
                    cout << "Первый стек пуст. Невозможно выполнить умножение." << endl;
                }
                break;
            case 3:
                cout << "Первый стек: " << stack1 << endl;
                break;
            case 4:
                if (stack1.isEmpty()) {
                    cout << "Первый стек пуст." << endl;
                } else {
                    cout << "Первый стек не пуст." << endl;
                }
                break;
            case 5:
                stack2 = stack1;
                cout << "Первый стек присвоен второму стеку." << endl;
                break;
            case 6:
                if (stack1 == stack2) {
                    cout << "Стеки равны." << endl;
                } else {
                    cout << "Стеки не равны." << endl;
                }
                break;
            case 7:
                exit = true;
                break;
            default:
                cout << "Неправильный выбор. Пожалуйста, выберите снова." << endl;
                break;
        }
    }

    return 0;
}
