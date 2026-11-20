#include <iostream>
#include <stdexcept>
#include <string>
#include <deque>

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
        for (int i = 0; i <= topIndex; i++) newData[i] = data[i];
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
        if (isEmpty()) throw underflow_error("Stack is empty");
        return data[topIndex--];
    }
    T top() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return data[topIndex];
    }
    bool isEmpty() const { return topIndex == -1; }
};

string decimalToBinary(int num) {
    if (num == 0) return "0";
    Stack<int> st;
    while (num > 0) {
        st.push(num % 2);
        num /= 2;
    }
    string result = "";
    while (!st.isEmpty()) {
        result += to_string(st.pop());
    }
    return result;
}

template <typename T>
class MaxQueue {
private:
    T* data;
    int frontIndex;
    int rearIndex;
    int capacity;
    int count;
    deque<T> maxDeque;
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) newData[i] = data[(frontIndex + i) % capacity];
        delete[] data;
        data = newData;
        frontIndex = 0;
        rearIndex = count;
        capacity = newCapacity;
    }
public:
    MaxQueue(int initialCapacity = 10) : capacity(initialCapacity), frontIndex(0), rearIndex(0), count(0) {
        data = new T[capacity];
    }
    ~MaxQueue() { delete[] data; }
    void enqueue(const T& value) {
        if (count >= capacity) resize();
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        while (!maxDeque.empty() && maxDeque.back() < value) maxDeque.pop_back();
        maxDeque.push_back(value);
        count++;
    }
    T dequeue() {
        if (isEmpty()) throw underflow_error("Queue is empty");
        T value = data[frontIndex];
        if (value == maxDeque.front()) maxDeque.pop_front();
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return value;
    }
    T getMax() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return maxDeque.front();
    }
    bool isEmpty() const { return count == 0; }
};

template <typename T>
class MaxDeque {
private:
    T* data;
    int frontIndex;
    int rearIndex;
    int capacity;
    int count;
    deque<T> maxDeque;
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) newData[i] = data[(frontIndex + i) % capacity];
        delete[] data;
        data = newData;
        frontIndex = 0;
        rearIndex = count;
        capacity = newCapacity;
    }
public:
    MaxDeque(int initialCapacity = 10) : capacity(initialCapacity), frontIndex(0), rearIndex(0), count(0) {
        data = new T[capacity];
    }
    ~MaxDeque() { delete[] data; }
    void push_back(const T& value) {
        if (count >= capacity) resize();
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        while (!maxDeque.empty() && maxDeque.back() < value) maxDeque.pop_back();
        maxDeque.push_back(value);
        count++;
    }
    void push_front(const T& value) {
        if (count >= capacity) resize();
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = value;
        while (!maxDeque.empty() && maxDeque.front() < value) maxDeque.pop_front();
        maxDeque.push_front(value);
        count++;
    }
    T getMax() const {
        if (isEmpty()) throw underflow_error("Deque is empty");
        return maxDeque.front();
    }
    bool isEmpty() const { return count == 0; }
};

template <typename T>
class PriorityQueue {
private:
    T* heap;
    int count;
    int capacity;
    void resize() {
        int newCapacity = capacity * 2;
        T* newHeap = new T[newCapacity];
        for (int i = 0; i < count; i++) newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else break;
        }
    }
    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            if (left < count && heap[left] > heap[largest]) largest = left;
            if (right < count && heap[right] > heap[largest]) largest = right;
            if (largest == index) break;
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }
public:
    PriorityQueue(int initialCapacity = 10) : capacity(initialCapacity), count(0) {
        heap = new T[capacity];
    }
    ~PriorityQueue() { delete[] heap; }
    void push(const T& value) {
        if (count >= capacity) resize();
        heap[count] = value;
        heapifyUp(count);
        count++;
    }
    T pop() {
        if (isEmpty()) throw underflow_error("PriorityQueue is empty");
        T maxValue = heap[0];
        heap[0] = heap[count - 1];
        count--;
        heapifyDown(0);
        return maxValue;
    }
    bool isEmpty() const { return count == 0; }
};

void heapSort(int arr[], int n) {
    PriorityQueue<int> pq(n);
    for (int i = 0; i < n; i++) pq.push(arr[i]);
    for (int i = n - 1; i >= 0; i--) arr[i] = pq.pop();
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "ЗАДАНИЕ 1: Стек (Десятичное в двоичное)" << endl;
    int num = 42;
    cout << "Число " << num << " в двоичной СС: " << decimalToBinary(num) << endl << endl;

    cout << "ЗАДАНИЕ 2: Очередь (Максимум за O(1))" << endl;
    MaxQueue<int> q;
    q.enqueue(10); q.enqueue(25); q.enqueue(5); q.enqueue(40);
    cout << "Максимум в очереди: " << q.getMax() << endl;
    q.dequeue(); q.dequeue(); q.dequeue();
    cout << "Максимум после удаления трех элементов: " << q.getMax() << endl << endl;

    cout << "ЗАДАНИЕ 3: Дек (Максимум за O(1))" << endl;
    MaxDeque<int> dq;
    dq.push_back(15); dq.push_back(8); dq.push_front(50); dq.push_back(20);
    cout << "Максимум в деке: " << dq.getMax() << endl << endl;

    cout << "ЗАДАНИЕ 4: Приоритетная очередь (Heap Sort)" << endl;
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapSort(arr, n);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}