#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

void reverseString(string& str, int start, int end) {
    if (start >= end) return;
    swap(str[start], str[end]);
    reverseString(str, start + 1, end - 1);
}

bool isPalindrome(const string& str, int start, int end) {
    if (start >= end) return true;
    if (str[start] != str[end]) return false;
    return isPalindrome(str, start + 1, end - 1);
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

long long measureSortTime(void (*sortFunc)(int[], int), int arr[], int n) {
    int* copy = new int[n];
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto end = high_resolution_clock::now();

    delete[] copy;
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== ЧАСТЬ 1: РЕКУРСИВНЫЕ АЛГОРИТМЫ ===" << endl;

    cout << "1. Факториал 5: " << factorial(5) << endl;
    cout << "2. Число Фибоначчи (10): " << fib(10) << endl;

    string s1 = "hello";
    reverseString(s1, 0, s1.length() - 1);
    cout << "3. Переворот строки 'hello': " << s1 << endl;

    string s2 = "radar";
    string s3 = "apple";
    cout << "4. 'radar' палиндром? " << (isPalindrome(s2, 0, s2.length() - 1) ? "Да" : "Нет") << endl;
    cout << "   'apple' палиндром? " << (isPalindrome(s3, 0, s3.length() - 1) ? "Да" : "Нет") << endl;

    cout << "\n=== ЧАСТЬ 2: ПРОСТЫЕ СОРТИРОВКИ ===" << endl;

    const int N = 5000;
    int* arr = new int[N];

    for (int i = 0; i < N; i++) {
        arr[i] = N - i;
    }

    cout << "Сравнение на массиве, отсортированном в обратном порядке (N = " << N << "):" << endl;

    long long tBubble = measureSortTime(bubbleSort, arr, N);
    cout << "Пузырьковая: " << tBubble << " мкс" << endl;

    long long tInsertion = measureSortTime(insertionSort, arr, N);
    cout << "Вставками: " << tInsertion << " мкс" << endl;

    long long tSelection = measureSortTime(selectionSort, arr, N);
    cout << "Выбором:    " << tSelection << " мкс" << endl;

    delete[] arr;
    return 0;
}