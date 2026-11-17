#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

template <typename T>
class Vector {
private:
    T* data;
    int sz;
    int cap;
    int copyCount;

public:
    class reverse_iterator {
    private:
        T* ptr;
    public:
        reverse_iterator(T* p = nullptr) : ptr(p) {}
        T& operator*() { return *(ptr - 1); }
        const T& operator*() const { return *(ptr - 1); }
        reverse_iterator& operator++() { --ptr; return *this; }
        reverse_iterator operator++(int) { reverse_iterator temp = *this; --ptr; return temp; }
        bool operator!=(const reverse_iterator& other) const { return ptr != other.ptr; }
        bool operator==(const reverse_iterator& other) const { return ptr == other.ptr; }
    };

    Vector() : data(nullptr), sz(0), cap(0), copyCount(0) {}

    explicit Vector(int n) : sz(n), cap(n), copyCount(0) {
        data = new T[cap];
        for (int i = 0; i < sz; i++) data[i] = T();
    }

    Vector(int n, const T& val) : sz(n), cap(n), copyCount(0) {
        data = new T[cap];
        for (int i = 0; i < sz; i++) data[i] = val;
    }

    Vector(const Vector& other) : sz(other.sz), cap(other.cap), copyCount(other.copyCount) {
        data = new T[cap];
        for (int i = 0; i < sz; i++) data[i] = other.data[i];
    }

    Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap), copyCount(other.copyCount) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    ~Vector() { delete[] data; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            copyCount = other.copyCount;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        std::swap(copyCount, other.copyCount);
    }

    T& operator[](int index) {
        if (index < 0 || index >= sz) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= sz) throw out_of_range("Index out of range");
        return data[index];
    }

    int size() const { return sz; }
    int capacity() const { return cap; }
    bool empty() const { return sz == 0; }

    void reserve(int newCap) {
        if (newCap <= cap) return;
        T* newData = new T[newCap];
        for (int i = 0; i < sz; i++) {
            newData[i] = data[i];
            copyCount++;
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

    void push_back(const T& value) {
        if (sz >= cap) {
            int newCap = cap == 0 ? 1 : cap * 2;
            reserve(newCap);
        }
        data[sz++] = value;
    }

    void pop_back() {
        if (empty()) throw underflow_error("Vector is empty");
        sz--;
    }

    void clear() { sz = 0; }
    int getCopyCount() const { return copyCount; }
    void resetCopyCount() { copyCount = 0; }

    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }

    reverse_iterator rbegin() { return reverse_iterator(data + sz); }
    reverse_iterator rend() { return reverse_iterator(data); }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== Демонстрация работы Vector (Продвинутый уровень) ===" << endl;
    Vector<int> v;

    for (int i = 1; i <= 5; i++) v.push_back(i * 10);

    cout << "Содержимое вектора (range-based for): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "Обратный вывод (reverse_iterator): ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n=== Амортизированный анализ push_back ===" << endl;
    cout << setw(10) << "n" << setw(15) << "Копирований" << setw(15) << "Всего операций" << setw(15) << "Среднее" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int n = 1000; n <= 100000; n *= 10) {
        Vector<int> vec;
        for (int i = 0; i < n; i++) vec.push_back(i);
        int totalOps = n + vec.getCopyCount();
        double average = (double)totalOps / n;
        cout << setw(10) << n << setw(15) << vec.getCopyCount() << setw(15) << totalOps << setw(15) << fixed << setprecision(2) << average << endl;
    }

    return 0;
}