#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Time {
private:
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
    void normalize();

public:
    // Конструкторы 
    Time();                                           // без аргументов
    Time(unsigned int h, unsigned int m, unsigned int s); // числами
    Time(const string& str);                          // строкой "HH:MM:SS"
    Time(unsigned long totalSeconds);                 // секундами
    Time(const Time& other);                          // копирование

    // Методы
    void read();
    void display() const;
    string toString() const;

    // Обязательные операции
    long differenceInSeconds(const Time& other) const;
    Time addSeconds(unsigned long secs) const;
    int compare(const Time& other) const;
    unsigned long toSeconds() const;
    unsigned int toMinutesRounded() const;
};

/* ==================== Реализация методов ==================== */


void Time::normalize() {
    unsigned long total = toSeconds();          
    hours = (total / 3600) % 24;
    minutes = (total % 3600) / 60;
    seconds = total % 60;
}

// Конструкторы
Time::Time() {
    hours = minutes = seconds = 0;
}

Time::Time(unsigned int h, unsigned int m, unsigned int s) {
    hours = h; minutes = m; seconds = s;
    normalize();
}

Time::Time(const string& str) {
    sscanf_s(str.c_str(), "%u:%u:%u", &hours, &minutes, &seconds);
    normalize();
}

Time::Time(unsigned long totalSeconds) {
    hours = (totalSeconds / 3600) % 24;
    minutes = (totalSeconds % 3600) / 60;
    seconds = totalSeconds % 60;
}

Time::Time(const Time& other) {
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
}

// Методы
void Time::read() {
    cout << "Введите часы (0-23): ";   cin >> hours;
    cout << "Введите минуты (0-59): "; cin >> minutes;
    cout << "Введите секунды (0-59): "; cin >> seconds;
    normalize();
}

void Time::display() const {
    cout << setfill('0') << setw(2) << hours << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
}

string Time::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
    return ss.str();
}

// показывает разность времени между моментами
long Time::differenceInSeconds(const Time& other) const {
    long s1 = toSeconds();
    long s2 = other.toSeconds();
    return abs(s1 - s2);
}

Time Time::addSeconds(unsigned long secs) const {
    return Time(toSeconds() + secs);
}

// сравнивает два момента времени true/false(1/-1)
int Time::compare(const Time& other) const {
    long s1 = toSeconds();
    long s2 = other.toSeconds();
    if (s1 == s2) return 0;
    return (s1 > s2) ? 1 : -1;
}

unsigned long Time::toSeconds() const {
    return hours * 3600UL + minutes * 60 + seconds;
}

// перевод в минуты с округлением
unsigned int Time::toMinutesRounded() const {
    return (toSeconds() + 30) / 60;
}

// ============================== main
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №3. Конструкторы" << endl;
    cout << "Вариант 10: Класс Time (час:минута:секунда)\n\n";

    cout << "=== РАЗЛИЧНЫЕ СПОСОБЫ СОЗДАНИЯ ОБЪЕКТОВ ===\n";

    Time t1;                         
    Time t2(23, 59, 58);             // числами
    Time t3("12:30:45");             // строкой
    Time t4(3665UL);                 // секундами (01:01:05)
    Time t5(t2);                     

    cout << "t1 (по умолчанию): "; t1.display(); cout << endl;
    cout << "t2 (числами):      "; t2.display(); cout << endl;
    cout << "t3 (строкой):      "; t3.display(); cout << endl;
    cout << "t4 (из секунд):    "; t4.display(); cout << endl;
    cout << "t5 (копия t2):     "; t5.display(); cout << endl;

    cout << "\n=== ВВОД С КЛАВИАТУРЫ ===\n";
    Time t6;
    t6.read();
    cout << "Вы ввели: "; t6.display(); cout << endl;

    cout << "\n=== МАССИВ ОБЪЕКТОВ ===\n";
    Time arr[4] = { Time(), Time(10,20,30), Time("00:05:00"), Time(86400UL) };
    for (int i = 0; i < 4; ++i) {
        cout << "arr[" << i << "] = ";
        arr[i].display();
        cout << "  =>  " << arr[i].toSeconds() << " сек\n";
    }

    cout << "\n=== ОПЕРАЦИИ ===\n";
    Time a(10, 15, 20);
    Time b(11, 30, 50);

    cout << "a = "; a.display(); cout << endl;
    cout << "b = "; b.display(); cout << endl;

    cout << "Разница: " << a.differenceInSeconds(b) << " сек\n";
    cout << "a + 5000 сек = "; a.addSeconds(5000).display(); cout << endl;

    int cmp = a.compare(b);
    cout << "Сравнение: " << (cmp < 0 ? "a раньше" : (cmp > 0 ? "a позже" : "равны")) << endl;

    cout << "a в секундах: " << a.toSeconds() << endl;
    cout << "a в минутах (округление): " << a.toMinutesRounded() << endl;

    cout << "\n=== toString ===\n";
    cout << "a: " << a.toString() << endl;
    cout << "b: " << b.toString() << endl;

    return 0;
}