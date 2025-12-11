#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// ============================= Шаблонный класс Optional<T>

template <typename T>
class Optional {
private:
    T value;           // хранимое значение
    bool has_value;    // флаг наличия значения

public:
    // Конструкторы
    Optional() : has_value(false) {}                          // пустой Optional
    Optional(const T& val) : value(val), has_value(true) {}   // с значением

    // Основные методы
    bool hasValue() const { return has_value; }

    // Получение значения (с проверкой)
    const T& getValue() const {
        if (!has_value) 
            throw runtime_error("Optional не содержит значения (getValue)");
        
        return value;
    }

    T& getValue() {
        if (!has_value) 
            throw runtime_error("Optional не содержит значения (getValue)");
        
        return value;
    }

    // Установка значения
    void setValue(const T& val) {
        value = val;
        has_value = true;
    }

    // Сброс (очистка)
    void reset() {
        has_value = false;
        // value уничтожается автоматически при выходе из области видимости
    }

    // Преобразование в строку
    string toString() const {
        if (!has_value) 
            return "empty";
        
        stringstream ss;
        ss << value;
        return ss.str();
        return ss.str();
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& out, const Optional& opt) {
        if (opt.has_value) 
            out << opt.value;
        
        else 
            out << "empty";
        
        return out;
    }

    friend istream& operator>>(istream& in, Optional& opt) {
        cout << "Введите значение (или 'empty' для очистки): ";
        string input;
        in >> input;

        if (input == "empty" || input == "Empty" || input == "EMPTY") 
            opt.reset();
        
        else {
            stringstream ss(input);
            T val;
            if (ss >> val && ss.eof()) 
                opt.setValue(val);
            
            else {
                cout << "Некорректный ввод — Optional оставлен пустым.\n";
                opt.reset();
            }
        }
        return in;
    }
};

// ============================= main

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Тестирование Optional<int> ===\n";

    Optional<int> opt1;                    // пустой
    cout << "opt1 (по умолчанию): " << opt1 << " | hasValue = "
        << (opt1.hasValue() ? "true" : "false") << endl;

    opt1.setValue(42);
    cout << "После setValue(42): " << opt1 << " | toString(): " << opt1.toString() << endl;

    cout << "Значение: " << opt1.getValue() << endl;

    Optional<int> opt2(100);               // сразу с значением
    cout << "opt2 (создан с 100): " << opt2 << endl;

    // Демонстрация ввода
    cout << "\n=== Ручной ввод для Optional<double> ===\n";
    Optional<double> optDouble;
    cin >> optDouble;
    cout << "Введено: " << optDouble << " | hasValue = " << optDouble.hasValue() << endl;

    // Очистка
    optDouble.reset();
    cout << "После reset(): " << optDouble << endl;

    // Попытка получить значение из пустого
    cout << "\nПопытка получить значение из пустого Optional:\n";
    try {
        int x = opt1.getValue();  // уже есть значение
        cout << "Успех: " << x << endl;

        Optional<string> emptyStr;
        cout << emptyStr.getValue();  // должно бросить исключение
    }
    catch (const exception& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    }

    // Работа со строками
    cout << "\n=== Optional<string> ===\n";
    Optional<string> name;
    name.setValue("Александр");
    cout << "Имя: " << name << endl;
    cout << "toString(): " << name.toString() << endl;

    
    return 0;
}