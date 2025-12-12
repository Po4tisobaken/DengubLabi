#include <iostream>
using namespace std;

// ============================================================================= constexpr хеш строки 
constexpr unsigned long long consteval_hash(const char* str) {
    unsigned long long hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(*str);
        ++str;
    }
    return hash;
}

// Для строковых литералов
template<std::size_t N>
constexpr unsigned long long hash_literal(const char(&str)[N]) {
    return consteval_hash(str);
}

// ============================================================================= main 
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Лаба№11_10: constexpr хеш строки ===\n\n";

    
    constexpr auto h1 = hash_literal("Hello");
    constexpr auto h2 = hash_literal("World");
    constexpr auto h3 = hash_literal("C++20");
    constexpr auto h4 = hash_literal("абвгд");
    constexpr auto h5 = hash_literal("");           // пустая строка
    constexpr auto h6 = hash_literal("AaAa");
    constexpr auto h7 = hash_literal("BBBB");

    cout << "\"Hello\"      -> " << h1 << "\n";
    cout << "\"World\"      -> " << h2 << "\n";
    cout << "\"C++20\"      -> " << h3 << "\n";
    cout << "\"абвгд\"      -> " << h4 << "\n";
    cout << "\"\"           -> " << h5 << "\n";
    cout << "\"AaAa\"       -> " << h6 << "\n";
    cout << "\BBBB\"        -> " << h7 << "\n";

    // Проверка коллизии 
    cout << "\nКоллизия \"AaAa\" и \"BBBB\": ";
    if constexpr (h6 == h7) {
        cout << "да (" << h6 << ")\n";
    }
    else {
        cout << "нет\n";
    }

    return 0;
}