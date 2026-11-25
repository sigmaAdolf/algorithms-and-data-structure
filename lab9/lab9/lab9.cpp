#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);
        return node;
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data) node->left = remove(node->left, key);
        else if (key > node->data) node->right = remove(node->right, key);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void kthLargestUtil(Node* node, int k, int& count) {
        if (node == nullptr || count >= k) return;
        kthLargestUtil(node->right, k, count);
        count++;
        if (count == k) {
            cout << "K-й наибольший элемент (" << k << "): " << node->data << endl;
            return;
        }
        kthLargestUtil(node->left, k, count);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key) != nullptr; }
    void remove(int key) { root = remove(root, key); }

    void printInOrder() {
        inOrder(root);
        cout << endl;
    }

    int getHeight() {
        return getHeight(root);
    }

    void findKthLargest(int k) {
        int count = 0;
        kthLargestUtil(root, k, count);
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    cout << "=== ЧАСТЬ 1: Высота дерева (Вариант 3) ===" << endl;
    BST tree1;
    tree1.insert(50);
    tree1.insert(30);
    tree1.insert(70);
    tree1.insert(20);
    tree1.insert(40);
    tree1.insert(60);
    tree1.insert(80);
    cout << "Высота дерева: " << tree1.getHeight() << endl << endl;

    cout << "=== ЧАСТЬ 2: K-й наибольший элемент (Вариант 3) ===" << endl;
    cout << "Симметричный обход: ";
    tree1.printInOrder();
    tree1.findKthLargest(2);
    cout << endl;

    cout << "=== ЧАСТЬ 3: Применение BST ===" << endl;
    BST tree2;
    cout << "Сгенерированные числа: ";
    for (int i = 0; i < 20; i++) {
        int num = rand() % 100;
        cout << num << " ";
        tree2.insert(num);
    }
    cout << endl;

    cout << "Отсортированная последовательность (in-order): ";
    tree2.printInOrder();

    cout << "Высота дерева: " << tree2.getHeight() << endl;

    int toDelete = 42;
    cout << "Удаляем элемент " << toDelete << "..." << endl;
    tree2.remove(toDelete);
    cout << "После удаления: ";
    tree2.printInOrder();

    return 0;
}