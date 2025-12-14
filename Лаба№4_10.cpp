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
    Time();
    Time(unsigned int h, unsigned int m, unsigned int s);
    Time(const string& str);
    Time(unsigned long totalSeconds);
    Time(const Time& other);

    // Методы
    string toString() const;
    unsigned long toSeconds() const;
    unsigned int toMinutesRounded() const;
    double length() const;

    // Перегруженные операции
    Time operator+(unsigned long secs) const;
    Time operator-(const Time& other) const;
    long operator-(unsigned long secs) const;
    int operator-(int dummy) const;

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator<=(const Time& other) const;

    // ======================== Перегрузка операторов ввода и вывода
    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& in, Time& t);
};

// ================================ Реализация методов
void Time::normalize() {
    unsigned long total = toSeconds();
    hours = (total / 3600) % 24;
    minutes = (total % 3600) / 60;
    seconds = total % 60;
}

Time::Time() : hours(0), minutes(0), seconds(0) {}

Time::Time(unsigned int h, unsigned int m, unsigned int s)
    : hours(h), minutes(m), seconds(s) {
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

Time::Time(const Time& other)
    : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
}

// Методы
string Time::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
    return ss.str();
}

unsigned long Time::toSeconds() const {
    return hours * 3600UL + minutes * 60 + seconds;
}

unsigned int Time::toMinutesRounded() const {
    return (toSeconds() + 30) / 60;
}

double Time::length() const {
    return static_cast<double>(toSeconds());
}

// Перегрузки арифметики и сравнения
Time Time::operator+(unsigned long secs) const {
    return Time(toSeconds() + secs);
}

Time Time::operator-(const Time& other) const {
    long diff = static_cast<long>(toSeconds()) - static_cast<long>(other.toSeconds());
    if (diff < 0) diff += 86400;
    return Time(diff);
}

long Time::operator-(unsigned long secs) const {
    return static_cast<long>(toSeconds()) - secs;
}

int Time::operator-(int) const { return 0; }

bool Time::operator==(const Time& other) const { return toSeconds() == other.toSeconds(); }
bool Time::operator!=(const Time& other) const { return !(*this == other); }
bool Time::operator>(const Time& other) const { return toSeconds() > other.toSeconds(); }
bool Time::operator<(const Time& other) const { return toSeconds() < other.toSeconds(); }
bool Time::operator>=(const Time& other) const { return toSeconds() >= other.toSeconds(); }
bool Time::operator<=(const Time& other) const { return toSeconds() <= other.toSeconds(); }

// ================================== Перегрузка потокового ввода/вывода
ostream& operator<<(ostream& out, const Time& t) {
    out << setfill('0') << setw(2) << t.hours << ":"
        << setw(2) << t.minutes << ":"
        << setw(2) << t.seconds;
    return out;
}

istream& operator>>(istream& in, Time& t) {
    unsigned int h, m, s;
    char colon1, colon2;
    in >> h >> colon1 >> m >> colon2 >> s;
    if (in.fail() || colon1 != ':' || colon2 != ':') {
        in.setstate(ios::failbit);
        return in;
    }
    t = Time(h, m, s);  // используем конструктор с нормализацией
    return in;
}

// =========================================================== main
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №4. Перегрузка операций" << endl;
    cout << "Вариант 10: Класс Time (час:минута:секунда)\n" << endl;

    Time a, b;

    cout << "\nВведите время a (формат чч:мм:сс): ";
    cin >> a;

    cout << "Введите время b (формат чч:мм:сс): ";
    cin >> b;

    Time c = b;  // копирование

    cout << "\nВремя a = " << a << endl;
    cout << "Время b = " << b << endl;
    cout << "Время c (копия b) = " << c << endl;

    cout << "\n=== ПЕРЕГРУЖЕННЫЕ ОПЕРАЦИИ ===\n";
    Time sum = a + 3665;
    cout << "a + 3665 сек = " << sum << endl;

    Time diffTime = a - b;
    cout << "a - b (как время) = " << diffTime << endl;

    long diffSec = a - b.toSeconds();
    cout << "a - b (в секундах) = " << diffSec << " сек" << endl;

    cout << "\nДлина (секунд с 00:00:00): a = " << a.length()
        << ", b = " << b.length() << endl;

    cout << "\n=== СРАВНЕНИЕ ===\n";
    cout << "a > b? " << (a > b ? "Да" : "Нет") << endl;
    cout << "a < b? " << (a < b ? "Да" : "Нет") << endl;
    cout << "a == b? " << (a == b ? "Да" : "Нет") << endl;
    cout << "a != b? " << (a != b ? "Да" : "Нет") << endl;

    cout << "\n=== СТАТИЧЕСКИЙ МАССИВ ===\n";
    Time arr[3];
    cout << "Введите 3 момента времени (формат чч:мм:сс):\n";
    for (int i = 0; i < 3; i++) {
        cout << "Время " << i + 1 << ": ";
        cin >> arr[i];
    }
    cout << "Статический массив:\n";
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    cout << "\n=== ДИНАМИЧЕСКИЙ МАССИВ ===\n";
    int n;
    cout << "Количество элементов: ";
    cin >> n;
    Time* dyn = new Time[n];
    cout << "Введите " << n << " моментов времени (формат чч:мм:сс):\n";
    for (int i = 0; i < n; i++) {
        cout << "Время " << i + 1 << ": ";
        cin >> dyn[i];
    }
    cout << "Динамический массив:\n";
    for (int i = 0; i < n; i++) {
        cout << "dyn[" << i << "] = " << dyn[i] << endl;
    }
    delete[] dyn;

    cout << "\n=== toString ===\n";
    cout << "1 как строка: " << a.toString() << endl;

    return 0;
}
