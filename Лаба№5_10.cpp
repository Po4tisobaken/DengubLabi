#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// ==================================== Класс Triad ====================================
class Triad {
protected:
    int a, b, c; 

public:
    Triad();
    Triad(int x, int y, int z);

    int getA() const;
    int getB() const;
    int getC() const;

    bool operator>(const Triad& t) const;
    bool operator<(const Triad& t) const;
    bool operator==(const Triad& t) const;
    bool operator!=(const Triad& t) const;

    friend ostream& operator<<(ostream& os, const Triad& t);
    friend istream& operator>>(istream& is, Triad& t);

    virtual string toString() const;
};

// Реализации методов Triad
Triad::Triad() : a(0), b(0), c(0) {}

Triad::Triad(int x, int y, int z) : a(x), b(y), c(z) {
    if (x < 0 || y < 0 || z < 0) {
        cout << "Ошибка: значения не могут быть отрицательными!\n";
        exit(1);
    }
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

ostream& operator<<(ostream& os, const Triad& t) {
    os << "(" << t.a << ", " << t.b << ", " << t.c << ")";
    return os;
}

istream& operator>>(istream& is, Triad& t) {
    int x, y, z;
    cout << "Введите три неотрицательных числа (a b c): ";
    is >> x >> y >> z;
    if (is.fail() || x < 0 || y < 0 || z < 0) {
        cout << "Ошибка ввода: значения должны быть неотрицательными целыми числами!\n";
        exit(1);
    }
    t.a = x; t.b = y; t.c = z;
    return is;
}

string Triad::toString() const {
    return "(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + ")";
}

// ==================================== Класс Date ====================================
class Date : public Triad {
public:
    Date();
    Date(int year, int month, int day);

    bool operator>(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator!=(const Date& d) const;

    friend ostream& operator<<(ostream& os, const Date& d);
    friend istream& operator>>(istream& is, Date& d);

    string toString() const override;
};

// Реализации методов Date
Date::Date() : Triad() {}

Date::Date(int year, int month, int day) : Triad(year, month, day) {
    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "Ошибка: некорректная дата!\n";
        exit(1);
    }
}

bool Date::operator>(const Date& d) const {
    if (a != d.a) return a > d.a; // год
    if (b != d.b) return b > d.b; // месяц
    return c > d.c;               // день
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

ostream& operator<<(ostream& os, const Date& d) {
    os << setfill('0') << setw(4) << d.a << "-"
        << setw(2) << d.b << "-"
        << setw(2) << d.c;
    return os;
}

istream& operator>>(istream& is, Date& d) {
    int day, month, year;
    cout << "Введите дату (день месяц год): ";
    is >> day >> month >> year;
    if (is.fail() || year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "Ошибка: некорректная дата или неверный ввод!\n";
        exit(1);
    }
    d.a = year;
    d.b = month;
    d.c = day;
    return is;
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
    cout << "Лабораторная работа №5. Наследование\n";
    cout << "Вариант 10: Triad → Date (тройка чисел → дата)\n\n";

    // ======================================== Работа с Triad
    cout << "=== Triad ===\n";
    Triad t1, t2;
    cin >> t1;
    cin >> t2;
    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;
    cout << "t1 > t2 : " << (t1 > t2 ? "true" : "false") << endl;
    cout << "t1 < t2 : " << (t1 < t2 ? "true" : "false") << endl;
    cout << "t1 == t2: " << (t1 == t2 ? "true" : "false") << "\n\n";

    // ============================= Работа с Date
    cout << "=== Date ===\n";
    Date d1, d2;
    cin >> d1;
    cin >> d2;
    cout << "d1 = " << d1 << endl;
    cout << "d2 = " << d2 << endl;
    cout << "d1 > d2 : " << (d1 > d2 ? "true" : "false") << endl;
    cout << "d1 < d2 : " << (d1 < d2 ? "true" : "false") << "\n\n";

    // ==================== Массивы объектов ====================
    cout << "\n=== Массивы объектов ===\n";
    Triad triadArr[2];
    Date dateArr[2];

    cout << "Введите 2 тройки:\n";
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ": ";
        cin >> triadArr[i];
    }
    cout << "\nМассив Triad:\n";
    for (int i = 0; i < 2; ++i) {
        cout << triadArr[i] << endl;
    }

    cout << "\nВведите 2 даты:\n";
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ": ";
        cin >> dateArr[i];
    }
    cout << "\nМассив Date:\n";
    for (int i = 0; i < 2; ++i) {
        cout << dateArr[i] << endl;
    }

    return 0;
}
