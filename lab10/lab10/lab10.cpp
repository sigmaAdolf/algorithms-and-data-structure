#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (node == nullptr) return nullptr;
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        else if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        return node;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr) return new AVLNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;
        return balance(node);
    }

    bool search(AVLNode* node, int key) {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key); }
};

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key) {
        if (node == nullptr) return new BSTNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    bool search(BSTNode* node, int key) {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    BST() : root(nullptr) {}
    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key); }
};

class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEndOfWord;
        TrieNode() : isEndOfWord(false) {
            for (int i = 0; i < 26; i++) children[i] = nullptr;
        }
    };
    TrieNode* root;

    void collectWords(TrieNode* node, string current, vector<string>& result) {
        if (node->isEndOfWord) result.push_back(current);
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                collectWords(node->children[i], current + char('a' + i), result);
            }
        }
    }

public:
    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) return false;
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) return false;
            current = current->children[index];
        }
        return true;
    }

    vector<string> getAllWords() {
        vector<string> result;
        collectWords(root, "", result);
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    cout << "=== ЧАСТЬ 1: AVL-дерево и Поиск (Вариант 3) ===" << endl;
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    cout << "Поиск 25 в AVL: " << (avl.search(25) ? "Найден" : "Не найден") << endl;
    cout << "Поиск 99 в AVL: " << (avl.search(99) ? "Найден" : "Не найден") << endl << endl;

    cout << "=== ЧАСТЬ 2: Trie (Вариант 3) ===" << endl;
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");
    trie.insert("dog");

    cout << "Поиск 'car': " << (trie.search("car") ? "Найден" : "Не найден") << endl;
    cout << "Поиск 'cattle': " << (trie.search("cattle") ? "Найден" : "Не найден") << endl;
    cout << "Поиск по префиксу 'ca': " << (trie.startsWith("ca") ? "Да" : "Нет") << endl;

    cout << "Все слова в Trie: ";
    vector<string> words = trie.getAllWords();
    for (const string& w : words) cout << w << " ";
    cout << endl << endl;

    cout << "=== ЧАСТЬ 3: Сравнение AVL и BST ===" << endl;
    int sizes[] = { 1000, 5000, 10000 };

    for (int n : sizes) {
        AVLTree avlTree;
        BST bstTree;

        vector<int> sortedData(n);
        for (int i = 0; i < n; i++) sortedData[i] = i;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) bstTree.insert(sortedData[i]);
        auto end = high_resolution_clock::now();
        long long bstTime = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) avlTree.insert(sortedData[i]);
        end = high_resolution_clock::now();
        long long avlTime = duration_cast<microseconds>(end - start).count();

        cout << "N = " << n << " (отсортированные данные):" << endl;
        cout << "  BST вставка: " << bstTime << " мкс" << endl;
        cout << "  AVL вставка: " << avlTime << " мкс" << endl;
    }

    return 0;
}