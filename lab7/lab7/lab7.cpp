#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <omp.h>

using namespace std;
using namespace chrono;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortSequential(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortSequential(arr, low, pi - 1);
        quickSortSequential(arr, pi + 1, high);
    }
}

void quickSortParallel(int arr[], int low, int high, int depth = 0) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (depth < 4) {
#pragma omp parallel sections
            {
#pragma omp section
                { quickSortParallel(arr, low, pi - 1, depth + 1); }

#pragma omp section
                { quickSortParallel(arr, pi + 1, high, depth + 1); }
            }
        }
        else {
            quickSortParallel(arr, low, pi - 1, depth + 1);
            quickSortParallel(arr, pi + 1, high, depth + 1);
        }
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    const int N = 500000;
    int* original = new int[N];
    for (int i = 0; i < N; i++) original[i] = rand() % N;

    cout << "=== Сравнение сортировок (N = " << N << ") ===" << endl;

    int* arr1 = new int[N];
    copy(original, original + N, arr1);
    auto start1 = high_resolution_clock::now();
    quickSortSequential(arr1, 0, N - 1);
    auto end1 = high_resolution_clock::now();
    cout << "Быстрая (обычная):       " << duration_cast<milliseconds>(end1 - start1).count() << " мс" << endl;
    delete[] arr1;

    int* arr2 = new int[N];
    copy(original, original + N, arr2);
    auto start2 = high_resolution_clock::now();
    quickSortParallel(arr2, 0, N - 1);
    auto end2 = high_resolution_clock::now();
    cout << "Быстрая (параллельная):  " << duration_cast<milliseconds>(end2 - start2).count() << " мс" << endl;
    delete[] arr2;

    int* arr3 = new int[N];
    copy(original, original + N, arr3);
    auto start3 = high_resolution_clock::now();
    mergeSort(arr3, 0, N - 1);
    auto end3 = high_resolution_clock::now();
    cout << "Сортировка слиянием:     " << duration_cast<milliseconds>(end3 - start3).count() << " мс" << endl;
    delete[] arr3;

    int* arr4 = new int[N];
    copy(original, original + N, arr4);
    auto start4 = high_resolution_clock::now();
    heapSort(arr4, N);
    auto end4 = high_resolution_clock::now();
    cout << "Пирамидальная:           " << duration_cast<milliseconds>(end4 - start4).count() << " мс" << endl;
    delete[] arr4;

    delete[] original;
    return 0;
}