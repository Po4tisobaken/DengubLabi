#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Шаблонный класс для узла дерева
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

// Шаблонный класс BinaryTree<T> (бинарное дерево поиска)
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    // Вспомогательные методы( Сделал для удобства)
    TreeNode<T>* insertHelper(TreeNode<T>* node, const T& value);
    TreeNode<T>* removeHelper(TreeNode<T>* node, const T& value);
    bool findHelper(TreeNode<T>* node, const T& value) const;
    void clearHelper(TreeNode<T>* node);
    void toStringHelper(TreeNode<T>* node, stringstream& ss) const;  

public:
    BinaryTree();
    ~BinaryTree();

    // Поиск элемента
    bool find(const T& value) const;

    // Добавление элемента
    void add(const T& value);

    // Удаление элемента
    void remove(const T& value);

    // Возврат содержимого в строке (toString) 
    string toString() const;

    // Вывод содержимого в поток (operator<<) 
    friend ostream& operator<<(ostream& out, const BinaryTree& tree) {
        stringstream ss;
        tree.toStringHelper(tree.root, ss);
        out << ss.str();
        return out;
    }

    // Чтение содержимого из потока (operator>>)
    friend istream& operator>>(istream& in, BinaryTree& tree) {
        tree.clear();  // Очищаем перед чтением
        int n;
        cout << "Введите количество элементов для дерева: ";
        in >> n;
        for (int i = 0; i < n; ++i) {
            T value;
            cout << "Элемент " << i + 1 << ": ";
            in >> value;
            tree.add(value);
        }
        return in;
    }

    // Очистка содержимого
    void clear();
};

//================================== Реализации методов 

// Конструктор
template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

// Деструктор
template <typename T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

// Вспомогательный метод для добавления 
template <typename T>
TreeNode<T>* BinaryTree<T>::insertHelper(TreeNode<T>* node, const T& value) {
    if (node == nullptr) {
        return new TreeNode<T>(value);
    }
    if (value < node->data) {
        node->left = insertHelper(node->left, value);
    }
    else if (value > node->data) {
        node->right = insertHelper(node->right, value);
    }  // Игнорируем дубликаты
    return node;
}

// Добавление элемента
template <typename T>
void BinaryTree<T>::add(const T& value) {
    root = insertHelper(root, value);
}

// Вспомогательный метод для поиска
template <typename T>
bool BinaryTree<T>::findHelper(TreeNode<T>* node, const T& value) const {
    if (node == nullptr) return false;
    if (value == node->data) return true;
    if (value < node->data) return findHelper(node->left, value);
    return findHelper(node->right, value);
}

// Поиск элемента
template <typename T>
bool BinaryTree<T>::find(const T& value) const {
    return findHelper(root, value);
}

// Вспомогательный метод для удаления 
template <typename T>
TreeNode<T>* BinaryTree<T>::removeHelper(TreeNode<T>* node, const T& value) {
    if (node == nullptr) return node;

    if (value < node->data) {
        node->left = removeHelper(node->left, value);
    }
    else if (value > node->data) {
        node->right = removeHelper(node->right, value);
    }
    else {
        // Узел найден
        if (node->left == nullptr) {
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        // найти минимальный в правом поддереве
        TreeNode<T>* temp = node->right;
        while (temp->left != nullptr) temp = temp->left;
        node->data = temp->data;
        node->right = removeHelper(node->right, temp->data);
    }
    return node;
}

// Удаление элемента
template <typename T>
void BinaryTree<T>::remove(const T& value) {
    root = removeHelper(root, value);
}

// Вспомогательный метод для очистки 
template <typename T>
void BinaryTree<T>::clearHelper(TreeNode<T>* node) {
    if (node != nullptr) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

// Очистка дерева
template <typename T>
void BinaryTree<T>::clear() {
    clearHelper(root);
    root = nullptr;
}

// Вспомогательный метод для toString 
template <typename T>
void BinaryTree<T>::toStringHelper(TreeNode<T>* node, stringstream& ss) const {
    if (node != nullptr) {
        toStringHelper(node->left, ss);
        ss << node->data << " ";
        toStringHelper(node->right, ss);
    }
}

// toString
template <typename T>
string BinaryTree<T>::toString() const {
    stringstream ss;
    toStringHelper(root, ss);
    string res = ss.str();
    if (!res.empty()) res.pop_back();  // Удаляем последний пробел
    return res.empty() ? "empty" : res;
}

//============== main
int main() {

    setlocale(LC_ALL, "RU");
    cout << "=====Лабораторная работа№9_11===== \n";
    cout << "=====Шаблоны====== \n\n";
    BinaryTree<int> tree;
    // Добавление элементов для теста
    tree.add(10);
    tree.add(20);
    tree.add(5);
    tree.add(15);
    tree.add(30);

    // Вывод через operator<<
    cout << "Дерево : " << tree << endl;

    // toString
    cout << "toString(): " << tree.toString() << endl;

    // Поиск
    cout << "Поиск 15: " << (tree.find(15) ? "найден" : "не найден") << endl;
    cout << "Поиск 50: " << (tree.find(50) ? "найден" : "не найден") << endl;

    // Удаление
    tree.remove(20);
    cout << "После удаления 20: " << tree << endl;

    // Ввод из потока
    cout << "\n=== Ввод нового дерева ===\n";
    cin >> tree;
    cout << "Новое дерево: " << tree << endl;

    // Очистка
    tree.clear();
    cout << "После очистки: " << tree << endl;

    // Демонстрация с string
    BinaryTree<string> strTree;
    strTree.add("banana");
    strTree.add("apple");
    strTree.add("cherry");
    cout << "\nСтрока дерево: " << strTree << endl;

    return 0;
}