#include <iostream>
#include <stdexcept>
#include <chrono>
#include <stack>

using namespace std;

template <typename T>
class Stack {
private:
    T* data;
    int topIndex;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (topIndex >= capacity - 1) {
            resize();
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw out_of_range("Стек пуст");
        }
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            throw out_of_range("Стек пуст");
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }
};

template <typename Func>
long long measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Анализ сложности операций стека ===" << endl;
    cout << "push: O(1) амортизированно (иногда O(n) при расширении)" << endl;
    cout << "pop: O(1)" << endl;
    cout << "top: O(1)" << endl;
    cout << "isEmpty: O(1)" << endl;
    cout << "size: O(1)" << endl << endl;

    cout << "--- Демонстрация работы ---" << endl;
    Stack<int> s(4); 
    for (int i = 1; i <= 5; i++) {
        s.push(i);
        cout << "push(" << i << "), размер: " << s.size() << endl;
    }
    cout << "Верхний элемент (top): " << s.top() << endl;
    cout << "Извлекаем (pop): " << s.pop();
    cout << "\nРазмер: " << s.size() << endl;

    cout << "\n=== Сравнение производительности: Свой Stack vs std::stack ===" << endl;
    cout << "Количество элементов: 1000000" << endl << endl;

    const int N = 1000000;

    long long timeMy = measureTime([] {
        Stack<int> myStack;
        for (int i = 0; i < N; i++) myStack.push(i);
        for (int i = 0; i < N; i++) myStack.pop();
        });

    long long timeStl = measureTime([] {
        stack<int> stlStack;
        for (int i = 0; i < N; i++) stlStack.push(i);
        for (int i = 0; i < N; i++) stlStack.pop();
        });

    cout << "Свой Stack (всего):   " << timeMy << " мкс" << endl;
    cout << "std::stack (всего):   " << timeStl << " мкс" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Свой Stack (на 1 оп.): " << (double)timeMy / (N * 2) << " мкс" << endl;
    cout << "std::stack (на 1 оп.): " << (double)timeStl / (N * 2) << " мкс" << endl;

    return 0;
}
