#include <iostream>
#include <cmath>
using namespace std;

struct Linear {
    double first;   // коэффициент A
    double second;  // коэффициент B (свободный член)

    void init(double a, double b);
    void read();
    void display() const;
    double function(double x) const;  // y = A*x + B
};

// Инициализация с проверкой 
void Linear::init(double a, double b) {
    first = a;
    second = b;
}

// Присвоение значений для коэффициентов
void Linear::read() {
    double a, b;
    cout << "Введите коэффициент A: ";
    cin >> a;
    cout << "Введите коэффициент B (свободный член): ";
    cin >> b;
    init(a, b);
}

// вывод уравнения на экран
void Linear::display() const {
    cout << "Линейное уравнение: y = " << first << " * x + " << second;
}


double Linear::function(double x) const {
    return first * x + second;
}

// Внешняя функция make_linear
Linear make_linear(double a, double b) {
    Linear eq;
    eq.init(a, b);
    return eq;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== Лабораторная работа №1. Структура-пара ===" << endl;
    cout << "=== Вариант 10: Линейное уравнение y = A*x + B ===\n" << endl;

    // 1. Статический объект
    cout << "=== 1. Статический объект ===" << endl;
    Linear eq1;
    eq1.init(2.5, -3.7);
    eq1.display();
    cout << "\nПри x = 10: y = " << eq1.function(10) << endl;

    // 2. Ввод с клавиатуры
    cout << "\n=== 2. Ввод с клавиатуры ===" << endl;
    Linear eq2;
    eq2.read();
    eq2.display();
    double x;
    cout << "\nВведите x для вычисления y: ";
    cin >> x;
    cout << "y = " << eq2.function(x) << endl;

    // 3. Создание через внешнюю функцию make_linear
    cout << "\n=== 3. Внешняя функция make_linear ===" << endl;
    Linear eq3 = make_linear(-1.5, 8.0);
    eq3.display();
    cout << "\nПри x = 4: y = " << eq3.function(4) << endl;

    // 4. Массив объектов
    cout << "\n=== 4. Массив объектов ===" << endl;
    Linear equations[4];
    equations[0].init(1.0, 0.0);    // y = x
    equations[1].init(0.0, 5.0);    // y = 5 (константа)
    equations[2].init(-2.0, 10);    // y = -2x + 10
    equations[3].init(3.14, -2.71); // y = πx - e

    for (int i = 0; i < 4; i++) {
        cout << "\nУравнение " << i + 1 << ": ";
        equations[i].display();
        cout << "  =>  при x = 2.0: y = " << equations[i].function(2.0);
    }
    cout << endl;

    // 5. Динамический объект
    cout << "\n=== 5. Динамический объект ===" << endl;
    Linear* eq4 = new Linear;
    eq4->init(0.5, 1.0);
    eq4->display();
    cout << "\nПри x = -6: y = " << eq4->function(-6) << endl;
    delete eq4;

    // 6. Различные интересные случаи
    cout << "\n=== 6. Различные случаи ===" << endl;

    Linear horizontal = make_linear(0.0, 7.5);
    cout << "Горизонтальная линия: ";
    horizontal.display();
    cout << " => y всегда = " << horizontal.function(100) << endl;

    Linear vertical_like; // имитируем "вертикальную" — большой наклон
    vertical_like.init(1000.0, 0.0);
    cout << "Практически вертикальная: ";
    vertical_like.display();
    cout << " => при x = 0.01: y = " << vertical_like.function(0.01) << endl;

    Linear identity = make_linear(1.0, 0.0);
    cout << "y = x: ";
    identity.display();
    cout << " => при x = 5: y = " << identity.function(5) << endl;

    return 0;
}