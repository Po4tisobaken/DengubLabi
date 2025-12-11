#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//========================================== Абстрактный базовый класс

class Base {
public:
    virtual void Input() = 0;
    virtual void Output() = 0;
    virtual ~Base() {}          
};


//======================================================== Класс Hex 
class Hex : public Base {
protected:
    unsigned char digits[100];   // 0..9, A..F (храним как числа 0–15)
    int length;                  // актуальное количество цифр (1..100)

public:
    Hex() {
        length = 1;
        memset(digits, 0, sizeof(digits));
    }

    void Input()  {
        cout << "\n--- Ввод Hex (шестнадцатеричное число) ---\n";
        string s;
        cout << "Введите число в шестнадцатеричной системе (до 100 цифр): ";
        cin >> s;

        // Убираем пробелы и переводим в верхний регистр
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

        // Заполняем массив: младшая цифра — в digits[0]
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
    }

    void Output()  {
        cout << "\n--- Вывод Hex ---\n";
        if (length == 1 && digits[0] == 0) {
            cout << "0" << endl;
            return;
        }

        cout << "0x";
        bool started = false;
        for (int i = length - 1; i >= 0; --i) {
            if (digits[i] != 0 || started) {
                started = true;
                if (digits[i] < 10)
                    cout << (int)digits[i];
                else
                    cout << (char)('A' + digits[i] - 10);
            }
        }
        if (!started) cout << "0";
        cout << endl;
    }
};


//========================================= Класс Fraction — дробное десятичное число


class Fraction : public Base {
protected:
    long long whole;              // целая часть (может быть отрицательной)
    unsigned char* frac_digits;   // цифры дробной части (0..9)
    int frac_len;                 // количество цифр после запятой
    bool sing;                    // знак (true — отрицательное)

public:
    Fraction() {
        whole = 0;
        sing = false;
        frac_len = 4;  // по умолчанию 4 знака
        frac_digits = new unsigned char[frac_len];
        memset(frac_digits, 0, frac_len);
    }

    ~Fraction() {
        delete[] frac_digits;
    }

    void Input()  {
        cout << "\n--- Ввод Fraction (дробное число) ---\n";
        cout << "Количество знаков после запятой (1–20 иначе будет 4): ";
        cin >> frac_len;
        if (frac_len < 1 || frac_len > 20) frac_len = 4;

        delete[] frac_digits;
        frac_digits = new unsigned char[frac_len];

        double value;
        cout << "Введите дробное число (например: -123.4567): ";
        cin >> value;

        if (value < 0) {
            sing = true;
            value = -value;
        }
        else 
            sing = false;
        

        whole = (long long)value;
        double fraction = value - whole;

        for (int i = 0; i < frac_len; ++i) {
            fraction *= 10;
            int digit = (int)fraction;
            frac_digits[i] = digit;
            fraction -= digit;
        }
    }

    void Output()  {
        cout << "\n--- Вывод Fraction ---\n";
        if (sing) cout << "-";
        cout << whole << ".";
        for (int i = 0; i < frac_len; ++i) {
            cout << (int)frac_digits[i];
        }
        cout << endl;
    }
};


//====================================== main

int main() {
    setlocale(LC_ALL, "Russian");

    Base* ptr;

    cout << "=== Лабораторная работа №6. Вариант 10 ===\n";
    cout << "Вариант: Hex + Fraction\n\n";

    // Демонстрация Hex
    Hex h;
    ptr = &h;
    ptr->Input();
    ptr->Output();

    // Демонстрация Fraction
    Fraction f;
    ptr = &f;
    ptr->Input();
    ptr->Output();

    cout << "\nПрограмма завершена.\n";
    return 0;
}