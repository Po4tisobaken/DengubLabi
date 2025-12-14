#include <iostream>
using namespace std;

// Перегрузка оператора << для вывода массива (указатель + размер)
template <typename T>
ostream& operator<<(ostream& os, const pair<T*, int>& p) {
    for (int i = 0; i < p.second; ++i) {
        os << p.first[i];
        if (i < p.second - 1) os << " ";
    }
    return os;
}

// Шаблонная функция сортировки вставками
template <typename T>
void sortInsert(T arr[], int size) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main() {
    setlocale(LC_ALL, "RU");  

    int arr1[] = { 5, 2, 8, 1, 9 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Массив int до сортировки: " << make_pair(arr1, size1) << endl;

    sortInsert(arr1, size1);

    cout << "Массив int после сортировки вставками: " << make_pair(arr1, size1) << endl << endl;

    double arr2[] = { 4.5, 1.2, 3.8, 2.1 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    cout << "Массив double до сортировки: " << make_pair(arr2, size2) << endl;

    sortInsert(arr2, size2);

    cout << "Массив double после сортировки вставками: " << make_pair(arr2, size2) << endl;

    return 0;
}
