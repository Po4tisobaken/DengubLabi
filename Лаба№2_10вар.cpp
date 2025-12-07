#include <iostream>
#include <string>
#include <sstream> // я пользовался ей для работы со строками и перевода строк во время
#include <iomanip>
using namespace std;

// =======================
// 1. СТРУКТУРА + ВНЕШНИЕ ФУНКЦИИ
// =======================
struct TimeStruct {
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    void init(unsigned int h, unsigned int m, unsigned int s);
    void read();
    void display() const;
    string toString() const;

    // Дополнительные виды инициализации
    void initFromString(const string& str);     // "23:59:59"
    void initFromSeconds(unsigned long totalSec);
    void initFromCurrent(TimeStruct t);
};

// Реализация методов структуры
void TimeStruct::init(unsigned int h, unsigned int m, unsigned int s) {
    hours = h % 24;
    minutes = m % 60;
    seconds = s % 60;
}

void TimeStruct::read() {
    unsigned int h, m, s;
    cout << "Введите часы (0-23): ";   cin >> h;
    cout << "Введите минуты (0-59): "; cin >> m;
    cout << "Введите секунды (0-59): "; cin >> s;
    init(h, m, s);
}

void TimeStruct::display() const {
    cout << setfill('0') << setw(2) << hours << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
}

string TimeStruct::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
    return ss.str();
}

void TimeStruct::initFromString(const string& str) {
    sscanf_s(str.c_str(), "%u:%u:%u", &hours, &minutes, &seconds);
    init(hours, minutes, seconds);
}

void TimeStruct::initFromSeconds(unsigned long totalSec) {
    hours = (totalSec / 3600) % 24;
    minutes = (totalSec % 3600) / 60;
    seconds = totalSec % 60;
}

void TimeStruct::initFromCurrent(TimeStruct t) {
    hours = t.hours;
    minutes = t.minutes;
    seconds = t.seconds;
}

// Внешние функции для операций
long differenceInSeconds(TimeStruct t1, TimeStruct t2) {
    long sec1 = t1.hours * 3600 + t1.minutes * 60 + t1.seconds;
    long sec2 = t2.hours * 3600 + t2.minutes * 60 + t2.seconds;
    return abs(sec1 - sec2);
}

TimeStruct addSeconds(TimeStruct t, unsigned long secs) {
    TimeStruct result = t;
    unsigned long total = t.hours * 3600 + t.minutes * 60 + t.seconds + secs;
    result.initFromSeconds(total);
    return result;
}

int compareTime(TimeStruct t1, TimeStruct t2) {
    long sec1 = t1.hours * 3600 + t1.minutes * 60 + t1.seconds;
    long sec2 = t2.hours * 3600 + t2.minutes * 60 + t2.seconds;
    if (sec1 == sec2) return 0;
    return (sec1 > sec2) ? 1 : -1;
}

unsigned long toSeconds(TimeStruct t) {
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

unsigned int toMinutesRounded(TimeStruct t) {
    return (t.hours * 3600 + t.minutes * 60 + t.seconds + 30) / 60;
}

// =======================
// 2. КЛАСС С ЗАКРЫТЫМИ ПОЛЯМИ
// =======================
class Time {
private:
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    void normalize() {
        hours = (hours % 24);
        minutes = (minutes % 60);
        seconds = (seconds % 60);
    }

public:
    // Конструкторы (4 вида инициализации)
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(unsigned int h, unsigned int m, unsigned int s) { init(h, m, s); }
    Time(const string& str) { initFromString(str); }
    Time(unsigned long totalSeconds) { initFromSeconds(totalSeconds); }

    // присваивает часы и нормализует их в 24-часовой формат
    void init(unsigned int h, unsigned int m, unsigned int s) {
        hours = h; minutes = m; seconds = s;
        normalize();
    }
    //
    void initFromString(const string& str) {
        sscanf_s(str.c_str(), "%u:%u:%u", &hours, &minutes, &seconds);
        normalize();
    }

    void initFromSeconds(unsigned long totalSec) {
        hours = (totalSec / 3600) % 24;
        minutes = (totalSec % 3600) / 60;
        seconds = totalSec % 60;
    }

    void read() {
        unsigned int h, m, s;
        cout << "Введите часы (0-23): ";   cin >> h;
        cout << "Введите минуты (0-59): "; cin >> m;
        cout << "Введите секунды (0-59): "; cin >> s;
        init(h, m, s);
    }

    void display() const {
        cout << setfill('0') << setw(2) << hours << ":"
            << setw(2) << minutes << ":"
            << setw(2) << seconds;
    }

    string toString() const {
        stringstream ss;
        ss << setfill('0') << setw(2) << hours << ":"
            << setw(2) << minutes << ":"
            << setw(2) << seconds;
        return ss.str();
    }

    // Операции
    long differenceInSeconds(const Time& other) const {
        long s1 = hours * 3600 + minutes * 60 + seconds;
        long s2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        return abs(s1 - s2);
    }

    Time addSeconds(unsigned long secs) const {
        Time result = *this;
        unsigned long total = toSeconds() + secs;
        result.initFromSeconds(total);
        return result;
    }

    int compare(const Time& other) const {
        long s1 = toSeconds();
        long s2 = other.toSeconds();
        if (s1 == s2) return 0;
        return (s1 > s2) ? 1 : -1;
    }

    unsigned long toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    unsigned int toMinutesRounded() const {
        return (toSeconds() + 30) / 60;
    }
};

// =======================
// ГЛАВНАЯ ФУНКЦИЯ
// =======================
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== Лабораторная работа №2. Структуры и классы ===" << endl;
    cout << "Вариант 10: Класс Time (час:минута:секунда)\n" << endl;

    // === РАБОТА СО СТРУКТУРОЙ ===
    cout << "=== 1. РАБОТА СО СТРУКТУРОЙ ===" << endl;
    TimeStruct t1, t2;

    cout << "Введите первое время:" << endl;
    t1.read();
    cout << "Введите второе время:" << endl;
    t2.read();

    cout << "\nПервое время: "; t1.display(); cout << endl;
    cout << "Второе время: "; t2.display(); cout << endl;

    cout << "Разница в секундах: " << differenceInSeconds(t1, t2) << endl;
    cout << "Первое время + 3665 сек: "; addSeconds(t1, 3665).display(); cout << endl;
    cout << "toString(): " << t1.toString() << endl;

    int cmpStruct = compareTime(t1, t2);
    cout << "Сравнение: " << (cmpStruct == 0 ? "равны" : (cmpStruct > 0 ? "t1 позже" : "t1 раньше")) << endl;

    // === РАБОТА С КЛАССОМ ===
    cout << "\n=== 2. РАБОТА С КЛАССОМ ===" << endl;

    Time ct1(23, 59, 58);
    Time ct2("12:30:45");
    Time ct3(90000);  // 25 часов → нормализуется до 01:00:00
    Time ct4;

    cout << "ct1 (конструктор числами): "; ct1.display(); cout << " => " << ct1.toString() << endl;
    cout << "ct2 (конструктор строкой): "; ct2.display(); cout << endl;
    cout << "ct3 (из секунд): "; ct3.display(); cout << endl;
    cout << "ct4 (ввод с клавиатуры): \n "; ct4.read(); ct4.display(); cout << endl;

    cout << "Разница ct1 и ct2: " << ct1.differenceInSeconds(ct2) << " сек" << endl;
    cout << "ct1 + 100 сек: "; ct1.addSeconds(100).display(); cout << endl;
    cout << "ct1 в секундах: " << ct1.toSeconds() << endl;
    cout << "ct1 в минутах (округление): " << ct1.toMinutesRounded() << endl;

    

    return 0;
}