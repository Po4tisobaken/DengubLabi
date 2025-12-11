#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// ==================================== Класс Triad ====================================

class Triad {
protected:
    int a, b, c;                    // три числа

public:
    Triad();
    Triad(int x, int y, int z);
    ~Triad() = default;             

    void set(int x, int y, int z);
    void read();

    int getA() const;
    int getB() const;
    int getC() const;

    bool operator>(const Triad& t) const;
    bool operator<(const Triad& t) const;
    bool operator==(const Triad& t) const;
    bool operator!=(const Triad& t) const;

    virtual string toString() const;
    void print() const;
};

// ================================== Реализации методов Triad
Triad::Triad() : a(0), b(0), c(0) {}

Triad::Triad(int x, int y, int z) {
    set(x, y, z);
}

void Triad::set(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0) {
        cout << "Ошибка: значения не могут быть отрицательными!\n";
        exit(1);
    }
    a = x;
    b = y;
    c = z;
}

void Triad::read() {
    int x, y, z;
    cout << "Введите три неотрицательных числа (a b c): ";
    cin >> x >> y >> z;
    set(x, y, z);
}

int Triad::getA() const { return a; }
int Triad::getB() const { return b; }
int Triad::getC() const { return c; }

bool Triad::operator>(const Triad& t) const {
    if (a != t.a) return a > t.a;
    if (b != t.b) return b > t.b;
    return c > t.c;
}

bool Triad::operator<(const Triad& t) const {
    return t > *this;
}

bool Triad::operator==(const Triad& t) const {
    return a == t.a && b == t.b && c == t.c;
}

bool Triad::operator!=(const Triad& t) const {
    return !(*this == t);
}

string Triad::toString() const {
    return "(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + ")";
}

void Triad::print() const {
    cout << toString() << endl;
}

// ==================================== Класс Date ====================================

class Date : public Triad {
public:
    Date();
    Date(int year, int month, int day);
    ~Date() = default;

    void read();

    bool operator>(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator!=(const Date& d) const;

    string toString() const ;   
};

// ==================================================Реализации методов Date
Date::Date() : Triad() {}

Date::Date(int year, int month, int day) : Triad(year, month, day) {
    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "Ошибка: некорректная дата!\n";
        exit(1);
    }
}

void Date::read() {
    int day, month, year;
    cout << "Введите дату (день месяц год): ";
    cin >> day >> month >> year;

    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "Ошибка: некорректная дата!\n";
        exit(1);
    }
    a = year;
    b = month;
    c = day;
}

bool Date::operator>(const Date& d) const {
    if (a != d.a) return a > d.a;      // год
    if (b != d.b) return b > d.b;      // месяц
    return c > d.c;                    // день
}

bool Date::operator<(const Date& d) const {
    return d > *this;
}

bool Date::operator==(const Date& d) const {
    return a == d.a && b == d.b && c == d.c;
}

bool Date::operator!=(const Date& d) const {
    return !(*this == d);
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(4) << a << "-"
        << setw(2) << b << "-"
        << setw(2) << c;
    return ss.str();
}

// ========================================================= main

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа №1. Наследование\n";
    cout << "Вариант 10: Triad → Date (тройка чисел → дата)\n\n";

    // ======================================== Работа с Triad 
    cout << "=== Triad ===\n";
    Triad t1, t2;

    cout << "Первая тройка:\n";  t1.read();
    cout << "Вторая тройка:\n";  t2.read();

    cout << "t1 = "; t1.print();
    cout << "t2 = "; t2.print();

    cout << "t1 > t2 : " << (t1 > t2 ? "true" : "false") << endl;
    cout << "t1 < t2 : " << (t1 < t2 ? "true" : "false") << endl;
    cout << "t1 == t2: " << (t1 == t2 ? "true" : "false") << "\n\n";

    // ============================= Работа с Date 
    cout << "=== Date ===\n";
    Date d1, d2;

    cout << "Первая дата:\n";  d1.read();
    cout << "Вторая дата:\n";  d2.read();

    cout << "d1 = " << d1.toString() << endl;
    cout << "d2 = " << d2.toString() << endl;

    cout << "d1 > d2 : " << (d1 > d2 ? "true" : "false") << endl;
    cout << "d1 < d2 : " << (d1 < d2 ? "true" : "false") << "\n\n";


    // ==================== Массивы объектов ====================
    cout << "\n=== Массивы объектов ===\n";

    Triad triadArr[2];
    Date  dateArr[2];

    cout << "Введите 2 тройки:\n";
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ": ";
        triadArr[i].read();
    }

    cout << "\nВведите 2 даты:\n";
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ": ";
        dateArr[i].read();
    }

    cout << "\nМассив Triad:\n";
    for (int i = 0; i < 2; ++i) triadArr[i].print();

    cout << "\nМассив Date:\n";
    for (int i = 0; i < 2; ++i) dateArr[i].print();

    cout << "\nПрограмма завершена успешно.\n";
    return 0;
}