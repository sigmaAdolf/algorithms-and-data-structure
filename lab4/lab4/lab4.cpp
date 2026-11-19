#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~SinglyLinkedList() { clear(); }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void print() const {
        Node* current = head;
        cout << "[";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << ", ";
            current = current->next;
        }
        cout << "]" << endl;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }
    bool empty() const { return head == nullptr; }
};

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList() { clear(); }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void printReverse() const {
        Node* current = tail;
        cout << "[";
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) cout << ", ";
            current = current->prev;
        }
        cout << "]" << endl;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }
    bool empty() const { return head == nullptr; }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Демонстрация работы списков(Вариант 3)" << endl;

    SinglyLinkedList<int> sList;
    for (int i = 1; i <= 5; i++) sList.push_back(i * 10);

    cout << "\nОдносвязный список: ";
    sList.print();
    cout << "Доступ по индексу sList[2]: " << sList[2] << endl;

    DoublyLinkedList<int> dList;
    for (int i = 1; i <= 5; i++) dList.push_back(i * 100);

    cout << "\nДвусвязный список (обратный вывод): ";
    dList.printReverse();
    cout << "Доступ по индексу dList[1]: " << dList[1] << endl;

    return 0;
}