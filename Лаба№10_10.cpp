#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// ====================================================================== Вспомогательные функции вывода

void printValue(int v) { cout << v << " "; }
void printValue(double v) { cout << v << " "; }
void printValue(bool v) { cout << (v ? "true" : "false") << " "; }
void printValue(const string& s) { cout << "\"" << s << "\" "; }
void printValue(const char* s) { cout << "\"" << s << "\" "; }

template<typename T>
void printValueWrapper(const T& value) {
    printValue(value);
}

// =======================================================================  C++11 версия — рекурсия
void groupByType11() {
    cout << "(пустой вызов)\n";
}

// Перегрузки для определения типа 
const char* getTypeName(int) { return "int"; }
const char* getTypeName(double) { return "double"; }
const char* getTypeName(bool) { return "bool"; }
const char* getTypeName(const string&) { return "string"; }
const char* getTypeName(const char*) { return "string"; }

// Универсальная обёртка для типов, которые не перечислил
template<typename T>
const char* getTypeName(const T&) { return "other"; }

template<typename First, typename... Rest>
void groupByType11(First&& first, Rest&&... rest) {
    static const char* lastType = nullptr;
    const char* currentType = getTypeName(first);

    if (!lastType || strcmp(lastType, currentType) != 0) {
        cout << "\n  " << currentType << ": ";
        lastType = currentType;
    }

    printValueWrapper(first);

    if (sizeof...(Rest) > 0) {
        groupByType11(rest...);
    }
    else {
        cout << "\n";
        lastType = nullptr;
    }
}

// ========================================================================================= C++17 версия — fold expressions

template<typename... Args>
void groupByType17(Args&&... args) {
    if (sizeof...(args) == 0) {
        cout << "(пустой вызов)\n";
        return;
    }

    cout << "Группировка по типам:\n";

    bool hasInt = false;
    (void)initializer_list<int>{ (is_same<Args, int>::value ? (hasInt = true, 0) : 0)... };
    if (hasInt) {
        cout << "  int: ";
        (void)initializer_list<int>{ (is_same<Args, int>::value ? (printValueWrapper(args), 0) : 0)... };
        cout << "\n";
    }

    bool hasDouble = false;
    (void)initializer_list<int>{ (is_same<Args, double>::value ? (hasDouble = true, 0) : 0)... };
    if (hasDouble) {
        cout << "  double: ";
        (void)initializer_list<int>{ (is_same<Args, double>::value ? (printValueWrapper(args), 0) : 0)... };
        cout << "\n";
    }

    bool hasBool = false;
    (void)initializer_list<int>{ (is_same<Args, bool>::value ? (hasBool = true, 0) : 0)... };
    if (hasBool) {
        cout << "  bool: ";
        (void)initializer_list<int>{ (is_same<Args, bool>::value ? (printValueWrapper(args), 0) : 0)... };
        cout << "\n";
    }

    bool hasString = false;
    (void)initializer_list<int>{ ((is_same<Args, string>::value || is_same<Args, const char*>::value) ? (hasString = true, 0) : 0)... };
    if (hasString) {
        cout << "  string: ";
        (void)initializer_list<int>{ ((is_same<Args, string>::value || is_same<Args, const char*>::value) ? (printValueWrapper(args), 0) : 0)... };
        cout << "\n";
    }

    bool hasOther = false;
    (void)initializer_list<int>{ ((!is_same<Args, int>::value && !is_same<Args, double>::value &&
        !is_same<Args, bool>::value && !is_same<Args, string>::value &&
        !is_same<Args, const char*>::value) ? (hasOther = true, 0) : 0)... };
    if (hasOther) {
        cout << "  other: ";
        (void)initializer_list<int>{ ((!is_same<Args, int>::value && !is_same<Args, double>::value &&
            !is_same<Args, bool>::value && !is_same<Args, string>::value &&
            !is_same<Args, const char*>::value) ? (printValueWrapper(args), 0) : 0)... };
        cout << "\n";
    }
}

// ======================================== main — вызываем обе версии

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Вариант 10: groupByType ===\n\n";

    cout << "1. C++11 версия (рекурсия):\n";
    groupByType11(10, 3.14, string("hello"), true, 42, string("world"), false, 2.718, 'A');
    cout << "\n---\n\n";

    cout << "2. C++17 версия (fold expressions):\n";
    groupByType17(10, 3.14, string("hello"), true, 42, string("world"), false, 2.718, 'A');

    cout << "\n---\n\n";
    cout << "3. Только строки (C++11):\n";
    groupByType11("яблоко", "банан", "вишня");

    cout << "\n---\n\n";
    cout << "4. Только строки (C++17):\n";
    groupByType17(string("яблоко"), string("банан"), string("вишня"));

    cout << "\n---\n\n";
    cout << "5. Пустой вызов (C++11):\n";
    groupByType11();

    cout << "\n---\n\n";
    cout << "6. Пустой вызов (C++17):\n";
    groupByType17();

    cout << "\nГотово!\n";
    return 0;
}