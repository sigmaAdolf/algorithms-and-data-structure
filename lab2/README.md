# Лабораторная работа №2: Анализ сложности алгоритмов. Шаблоны классов

**Студент:** Аджамян Рудик Агаронович  
**Группа:** ПИЖ-б-о-25-2(1)  
**Дисциплина:** Алгоритмы и структура данных  
**Вариант:** 3  
**Уровень:** Продвинутый  
**Тема индивидуального задания:** Реализация шаблонного контейнера `Stack<T>` с анализом сложности и сравнением с STL.  

**Проверила:** Белик Ангелина Игоревна  

## 1. Цель работы  
1. Научиться оценивать эффективность алгоритмов с помощью О-нотации (Big O).
2. Освоить классы сложности: O(1), O(log n), O(n), O(n log n), O(n²).
3. Научиться проводить экспериментальный анализ производительности алгоритмов.
4. Освоить создание шаблонов функций и классов для работы с различными типами данных.
5. Получить навыки сравнения производительности различных реализаций одной задачи.

## 2. Индивидуальное задание
Согласно индивидуальному заданию, вариант 3 продвинутого уровня, необходимо:
1. Реализовать шаблонный контейнер `Stack<T>`.
2. Предусмотреть операции: `push`, `pop`, `top`, `isEmpty`, `size`.
3. Провести анализ сложности каждой операции.
4. Экспериментально сравнить производительность собственной реализации с аналогом из STL (`std::stack`).

## 3. Проектирование классов

### 3.1. Класс `Stack<T>`
Реализован на основе динамического массива. При добавлении элемента, если массив заполнен, происходит его расширение (выделение памяти в 2 раза больше и копирование старых элементов). 

![Класс Stack](screenshots/img-1.png)   
Рисунок 1 - Результат работы контейнера Stack

### 3.2. Анализ сложности операций
- **`push` (добавление)**: O(1) в среднем (амортизированная сложность). В худшем случае, при расширении массива, сложность составляет O(n), так как требуется скопировать все элементы.
- **`pop` (удаление)**: O(1). Удаляется верхний элемент, сдвиг элементов не требуется.
- **`top` (просмотр верхнего)**: O(1). Просто чтение элемента по индексу `topIndex`.
- **`isEmpty`**: O(1). Сравнение индекса с -1.
- **`size`**: O(1). Возврат `topIndex + 1`.

## 4. Реализация программы
Ниже представлен исходный код программы, реализующий шаблонный контейнер и замер производительности.

```cpp
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

    ~Stack() { delete[] data; }

    void push(const T& value) {
        if (topIndex >= capacity - 1) resize();
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) throw out_of_range("Стек пуст");
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) throw out_of_range("Стек пуст");
        return data[topIndex];
    }

    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
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
    cout << "Извлекаем (pop): " << s.pop() << ", размер: " << s.size() << endl;

    cout << "\n=== Сравнение производительности: Свой Stack vs std::stack ===" << endl;
    cout << "Элементов\tСвой (мкс)\tSTL (мкс)" << endl;
    
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

    cout << N << "\t\t" << timeMy << "\t\t" << timeStl << endl;
    
    return 0;
}
