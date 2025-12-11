#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
using namespace std;

// ======================================== Мои классы-исключения


// 1.1 Пустой класс-исключение
class EmptyFractionException {};

// 1.2 Независимый класс с полями
class CustomFractionException {
private:
    long long numerator;
    long long denominator;
    string message;
public:
    CustomFractionException(long long num, long long den, const string& msg)
        : numerator(num), denominator(den), message(msg) {
    }

    //геттеры
    string getMessage() const { return message; }
    long long getNumerator() const { return numerator; }
    long long getDenominator() const { return denominator; }
};

// 1.3 Наследник от стандартного исключения
class FractionException : public logic_error {
private:
    long long numerator;
    long long denominator;
public:
    FractionException(long long num, long long den, const string& msg)
        : logic_error(msg), numerator(num), denominator(den) {
    }

    long long getNumerator() const { return numerator; }
    long long getDenominator() const { return denominator; }
};

// ======================================== Функции для вычисления целой части дроби


//====================================== 2.1 Без спецификации исключений + стандартные исключения
long long integerPart1(long long num, long long den) {
    if (den == 0) 
        throw invalid_argument("Знаменатель не может быть равен нулю");
    
    if (den < 0) {
        // Приводим к правильному виду: знак всегда в числителе
        num = -num;
        den = -den;
    }
    return num / den; // Целочисленное деление в C++ отбрасывает дробную часть к нулю
}

// =========================================================== 2.2 С throw() 
long long integerPart2(long long num, long long den) throw()  {
    if (den == 0) 
        throw runtime_error("Деление на ноль в integerPart2");
    
    return num / den;
}

// ================================================== 2.3 Стандартное исключение
long long integerPart3(long long num, long long den) throw(invalid_argument) {
    if (den == 0) 
        throw invalid_argument("Знаменатель равен нулю");
    
    if (den < 0) {
        num = -num;
        den = -den;
    }
    return num / den;
}

// =================================2.4 мои исключения  (все три вида)
long long integerPart4(long long num, long long den)
throw(EmptyFractionException, CustomFractionException, FractionException) {
    if (den == 0) {
        if (num == 0) 
            throw EmptyFractionException(); // 0/0 — неопределённость
        
        else 
            throw CustomFractionException(num, den, "Деление на ноль");
        
    }

    if (den < 0) {
        num = -num;
        den = -den;
    }

    if (abs(num) > 1e12 || abs(den) > 1e12) 
        throw FractionException(num, den, "Слишком большие значения — возможное переполнение");
    

    return num / den;
}

//================================== main
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа№7: Механизм обработки исключений\n";
    cout << "Вариант 10: Целая часть неправильной дроби num/den\n\n";

    // Вспомогательная структура для теста, чтобы не тратить время на ввод данных для проверки
    struct Test {
        long long num, den;
        const char* desc;
    };

    Test tests[] = {
        { 25, 4,   "25/4 = 6" },
        { -17, 3,  "-17/3 = -5" },
        { 10, -5,  "10/-5 = -2" },
        { 0, 7,    "0/7 = 0" },
        { 5, 0,    "5/0 — ошибка" },
        { 0, 0,    "0/0 — неопределённость" },
        { 1000000000000000, 1, "Очень большое число" }
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    cout << "=== Вариант 1: Без спецификации (стандартные исключения) ===\n";
    for (int i = 0; i < n; ++i) {
        cout << tests[i].desc << " -> ";
        try {
            long long res = integerPart1(tests[i].num, tests[i].den);
            cout << res;
        }
        catch (const invalid_argument& e) {
            cout << "ОШИБКА: " << e.what();
        }
        catch (...) {
            cout << "Неизвестная ошибка";
        }
        cout << endl;
    }

    cout << "\n=== Вариант 2: throw() — функция не должна бросать исключения ===\n";
    for (int i = 0; i < n; ++i) {
        cout << tests[i].desc << " -> ";
        try {
            long long res = integerPart2(tests[i].num, tests[i].den);
            cout << res;
        }
        catch (const runtime_error& e) {
            cout << "НАРУШЕНИЕ! " << e.what();
        }
        catch (...) {
            cout << "Неизвестное нарушение спецификации";
        }
        cout << endl;
    }

    cout << "\n=== Вариант 3: throw(invalid_argument) ===\n";
    for (int i = 0; i < n; ++i) {
        cout << tests[i].desc << " -> ";
        try {
            long long res = integerPart3(tests[i].num, tests[i].den);
            cout << res;
        }
        catch (const invalid_argument& e) {
            cout << "ОШИБКА: " << e.what();
        }
        cout << endl;
    }

    cout << "\n=== Вариант 4: Собственные исключения (все три вида) ===\n";
    for (int i = 0; i < n; ++i) {
        cout << tests[i].desc << " -> ";
        try {
            long long res = integerPart4(tests[i].num, tests[i].den);
            cout << res;
        }
        catch (const EmptyFractionException&) {
            cout << "ОШИБКА (EmptyFractionException): 0/0 — неопределённость";
        }
        catch (const CustomFractionException& e) {
            cout << "ОШИБКА (Custom): " << e.getMessage()
                << " (num=" << e.getNumerator() << ", den=" << e.getDenominator() << ")";
        }
        catch (const FractionException& e) {
            cout << "ОШИБКА (FractionException): " << e.what()
                << " (num=" << e.getNumerator() << ", den=" << e.getDenominator() << ")";
        }
        catch (...) {
            cout << "Неизвестная ошибка";
        }
        cout << endl;
    }

    
    return 0;
}