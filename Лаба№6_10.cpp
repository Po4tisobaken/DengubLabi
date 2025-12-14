#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <memory> // использовал для корректного вывода для дробных чисел 

using namespace std;

//==========================================
// Абстрактный базовый класс
class Base {
public:
    virtual ~Base() = default;

    //============== Перегружаем операторы ввода/вывода
    virtual istream& input(istream& is) = 0;
    virtual ostream& output(ostream& os) const = 0;
};

//========== Перегруженные глобальные операторы для удобства
istream& operator>>(istream& is, Base& obj) {
    return obj.input(is);
}

ostream& operator<<(ostream& os, const Base& obj) {
    return obj.output(os);
}

//========================================================
// Класс Hex (оставляем без изменений, кроме реализации через потоки)
class Hex : public Base {
protected:
    unsigned char digits[100]; // 0..15
    int length;

public:
    Hex() : length(1) {
        memset(digits, 0, sizeof(digits));
    }

    istream& input(istream& is) override {
        cout << "\n--- Ввод Hex (шестнадцатеричное число) ---\n";
        cout << "Введите число в шестнадцатеричной системе (до 100 цифр): ";
        string s;
        is >> s;

        string cleaned;
        for (char c : s) {
            if (c != ' ') cleaned += toupper(c);
        }

        length = cleaned.size();
        if (length > 100) {
            cout << "Слишком длинное число! Будут взяты младшие 100 цифр.\n";
            cleaned = cleaned.substr(cleaned.size() - 100);
            length = 100;
        }
        if (length == 0) {
            length = 1;
            cleaned = "0";
        }

        memset(digits, 0, sizeof(digits));
        for (int i = 0; i < length; ++i) {
            char c = cleaned[length - 1 - i];
            if (c >= '0' && c <= '9') digits[i] = c - '0';
            else if (c >= 'A' && c <= 'F') digits[i] = 10 + (c - 'A');
            else {
                cout << "Некорректный символ '" << c << "'. Будет заменён на 0.\n";
                digits[i] = 0;
            }
        }
        return is;
    }

    ostream& output(ostream& os) const override {
        os << "\n--- Вывод Hex ---\n";
        if (length == 1 && digits[0] == 0) {
            os << "0" << endl;
            return os;
        }
        os << "0x";
        bool started = false;
        for (int i = length - 1; i >= 0; --i) {
            if (digits[i] != 0 || started) {
                started = true;
                if (digits[i] < 10)
                    os << (int)digits[i];
                else
                    os << (char)('A' + digits[i] - 10);
            }
        }
        if (!started) os << "0";
        os << endl;
        return os;
    }
};

//========================================= Класс Fraction с перегрузкой >> и <<
class Fraction : public Base {
protected:
    long long whole;                                      // целая часть
    std::unique_ptr<unsigned char[]> frac_digits;         // цифры дробной части
    int frac_len;                                         // количество знаков после запятой
    bool sign;                                            // true — отрицательное

public:
    Fraction() : whole(0), frac_len(4), sign(false) {
        frac_digits = std::make_unique<unsigned char[]>(frac_len);
        memset(frac_digits.get(), 0, frac_len);
    }

    // Перегрузка оператора ввода >>
    istream& input(istream& is) override {
        cout << "\n--- Ввод Fraction (дробное число) ---\n";
        cout << "Количество знаков после запятой (1–20 иначе будет 4): ";
        int len;
        if (!(is >> len) || len < 1 || len > 20) {
            len = 4;
            cout << "Некорректное значение, будет использовано 4.\n";
        }
        frac_len = len;
        frac_digits = std::make_unique<unsigned char[]>(frac_len);
        memset(frac_digits.get(), 0, frac_len);

        double value;
        cout << "Введите дробное число (например: -123.4567): ";
        is >> value;

        sign = (value < 0);
        if (sign) value = -value;

        whole = (long long)value;
        double fraction = value - whole;

        for (int i = 0; i < frac_len; ++i) {
            fraction *= 10;
            int digit = (int)fraction;
            frac_digits[i] = digit;
            fraction -= digit;
        }
        return is;
    }

    // Перегрузка оператора вывода <<
    ostream& output(ostream& os) const override {
        os << "\n--- Вывод Fraction ---\n";
        if (sign) os << "-";
        os << whole << ".";
        for (int i = 0; i < frac_len; ++i) {
            os << (int)frac_digits[i];
        }
        os << endl;
        return os;
    }
};

//====================================== main
int main() {
    setlocale(LC_ALL, "Russian");

    Base* ptr;

    cout << "=== Лабораторная работа №6. Вариант 10 ===\n";
    cout << "Вариант: Hex + Fraction\n\n";

    // Демонстрация Hex через потоки
    Hex h;
    ptr = &h;
    cin >> *ptr;   
    cout << *ptr; 

    // Демонстрация Fraction через потоки
    Fraction f;
    ptr = &f;
    cin >> *ptr;
    cout << *ptr;

    cout << "\nПрограмма завершена.\n";
    return 0;
}
