#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int binarySearchFirst(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}

class HashTableQuadratic {
private:
    struct Entry {
        int key;
        int value;
        bool occupied;
        bool deleted;
        Entry() : key(0), value(0), occupied(false), deleted(false) {}
    };

    vector<Entry> table;
    int size;
    int count;

    int hashFunc(int key) const {
        return abs(key) % size;
    }

public:
    HashTableQuadratic(int s = 100003) : size(s), count(0) {
        table.resize(size);
    }

    void insert(int key, int value) {
        if (count * 2 >= size) return;

        int index = hashFunc(key);
        int i = 0;

        while (i < size) {
            int pos = (index + i * i) % size;

            if (!table[pos].occupied || table[pos].deleted) {
                table[pos].key = key;
                table[pos].value = value;
                table[pos].occupied = true;
                table[pos].deleted = false;
                count++;
                return;
            }
            if (table[pos].occupied && !table[pos].deleted && table[pos].key == key) {
                table[pos].value = value;
                return;
            }
            i++;
        }
    }

    int find(int key) {
        int index = hashFunc(key);
        int i = 0;

        while (i < size) {
            int pos = (index + i * i) % size;

            if (!table[pos].occupied && !table[pos].deleted) {
                return -1;
            }
            if (table[pos].occupied && !table[pos].deleted && table[pos].key == key) {
                return table[pos].value;
            }
            i++;
        }
        return -1;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    const int N = 100000;
    vector<int> arr(N);

    for (int i = 0; i < N; i++) {
        arr[i] = i / 2;
    }

    HashTableQuadratic ht(N * 2);
    for (int i = 0; i < N; i++) {
        ht.insert(arr[i], arr[i]);
    }

    int target = 25000;
    int queries = 10000;

    cout << "=== Сравнение поиска (N = " << N << ") ===" << endl;
    cout << "Ищем элемент: " << target << " (" << queries << " раз)" << endl << endl;

    auto start1 = high_resolution_clock::now();
    for (int i = 0; i < queries; i++) {
        binarySearchFirst(arr, target);
    }
    auto end1 = high_resolution_clock::now();
    cout << "Двоичный поиск (O(log n)): " << duration_cast<microseconds>(end1 - start1).count() << " мкс" << endl;

    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < queries; i++) {
        ht.find(target);
    }
    auto end2 = high_resolution_clock::now();
    cout << "Хеш-таблица (O(1)):        " << duration_cast<microseconds>(end2 - start2).count() << " мкс" << endl;

    return 0;
}