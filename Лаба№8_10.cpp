#include <iostream>
using namespace std;

// Шаблонная функция для сортировки 
template <typename T>
void sortInsert(T arr[], int size);

// Функция для вывода массива
template <typename T>
void printArray(T arr[], int size);

template <typename T>
void sortInsert(T arr[], int size) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    int arr1[] = { 5, 2, 8, 1, 9 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Массив до сортировки: ";
    printArray(arr1, size1);
    sortInsert(arr1, size1);
    cout << "Массив после сортировки вставками: ";
    printArray(arr1, size1);

    double arr2[] = { 4.5, 1.2, 3.8, 2.1 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Массив до сортировки: ";
    printArray(arr2, size2);
    sortInsert(arr2, size2);
    cout << "Массив после сортировки вставками: ";
    printArray(arr2, size2);

    return 0;
}