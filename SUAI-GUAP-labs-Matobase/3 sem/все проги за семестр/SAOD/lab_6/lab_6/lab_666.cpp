//lab6 var 10
#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BalancedBST {
private:
    TreeNode* root;

    TreeNode* sortedArrayToBST(std::vector<int>& sortedArray, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode* node = new TreeNode(sortedArray[mid]);

        node->left = sortedArrayToBST(sortedArray, start, mid - 1);
        node->right = sortedArrayToBST(sortedArray, mid + 1, end);

        return node;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    int getBalanceFactor(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }

    TreeNode* findMax(TreeNode* node) {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    TreeNode* insert(TreeNode* node, int val, bool& balanceNeeded) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->data) {
            node->left = insert(node->left, val, balanceNeeded);
        }
        else if (val > node->data) {
            node->right = insert(node->right, val, balanceNeeded);
        }
        else {
            return node;  
        }

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1 && val < node->left->data) {
            return rightRotate(node);
        }
        if (balanceFactor < -1 && val > node->right->data) {
            return leftRotate(node);
        }
        if (balanceFactor > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* remove(TreeNode* node, int key, bool& balanceNeeded) {
        if (node == nullptr)
            return node;

        if (key < node->data)
            node->left = remove(node->left, key, balanceNeeded);
        else if (key > node->data)
            node->right = remove(node->right, key, balanceNeeded);
        else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                TreeNode* temp = (node->left == nullptr) ? node->right : node->left;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }

                delete temp;
            }
            else {
                TreeNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data, balanceNeeded);
            }
        }

        if (node == nullptr)
            return node;

        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }


    bool search(TreeNode* node, int val, int& steps) {
        if (node == nullptr)
            return false;

        steps++;

        if (node->data == val)
            return true;
        else if (val < node->data)
            return search(node->left, val, steps);
        else
            return search(node->right, val, steps);
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void printTree(TreeNode* node, int indent = 0) {
        if (node == nullptr)
            return;
        printTree(node->right, indent + 4);
        for (int i = 0; i < indent; i++)
            std::cout << " ";
        std::cout << node->data << "\n";
        printTree(node->left, indent + 4);
    }

    void preorderTraversal(TreeNode* node, std::vector<int>& result) {
        if (node == nullptr)
            return;
        result.push_back(node->data);
        preorderTraversal(node->left, result);
        preorderTraversal(node->right, result);
    }

    TreeNode* balanceTree(std::vector<int>& sortedArray, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode* node = new TreeNode(sortedArray[mid]);

        node->left = balanceTree(sortedArray, start, mid - 1);
        node->right = balanceTree(sortedArray, mid + 1, end);

        return node;
    }

    void processTree(TreeNode* node, int& prev, bool isRoot = true) {
        if (node == nullptr)
            return;

        // Заменить отрицательные элементы на их абсолютные значения
        node->data = std::abs(node->data);

        // Уменьшить элементы, делящиеся на 4 без остатка
        if (node->data % 4 == 0)
            node->data /= 2;

        // Если это не корень дерева и prev не равно 0, вычесть предыдущее значение
        if (!isRoot && prev != 0)
            node->data = std::abs(node->data - prev);

        prev = node->data;

        processTree(node->left, prev, false);
        processTree(node->right, prev, false);
    }

public:
    BalancedBST() : root(nullptr) {}

    void insert(int val) {
        std::vector<int> sortedElements = preorderTraversal();
        sortedElements.push_back(val);
        std::sort(sortedElements.begin(), sortedElements.end());
        root = sortedArrayToBST(sortedElements, 0, sortedElements.size() - 1);
    }

    void remove(int val) {
        bool balanceNeeded = false; // Создание переменной для передачи в функцию remove
        root = remove(root, val, balanceNeeded);
        if (balanceNeeded) {
            std::vector<int> sortedElements = preorderTraversal();
            root = balanceTree(sortedElements, 0, sortedElements.size() - 1);
        }
    }

    bool search(int val, int& steps) {
        steps = 0;
        return search(root, val, steps);
    }

    void printTree() {
        printTree(root);
    }

    std::vector<int> preorderTraversal() {
        std::vector<int> result;
        preorderTraversal(root, result);
        return result;
    }

    void processTree() {
        int prev = 0;
        processTree(root, prev);
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    BalancedBST tree;

    int choice;
    int value;
    int steps;

    while (true) {
        std::cout << "1. Добавить элемент" << std::endl;
        std::cout << "2. Удалить элемент" << std::endl;
        std::cout << "3. Найти элемент" << std::endl;
        std::cout << "4. Вывести дерево" << std::endl;
        std::cout << "5. Прямой обход вершин" << std::endl;
        std::cout << "6. Обработать дерево" << std::endl;
        std::cout << "7. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение для вставки: ";
            std::cin >> value;
            tree.insert(value);
            break;
        case 2:
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            tree.remove(value);
            break;
        case 3:
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            if (tree.search(value, steps))
                std::cout << value << " найден за " << steps << " шагов." << std::endl;
            else
                std::cout << value << " не найден." << std::endl;
            break;
        case 4:
            std::cout << "Дерево:" << std::endl;
            tree.printTree();
            break;
        case 5:
            std::cout << "Прямой обход вершин: ";
            for (int val : tree.preorderTraversal())
                std::cout << val << " ";
            std::cout << std::endl;
            break;
        case 6:
            tree.processTree();
            std::cout << "Дерево обработано." << std::endl;
            break;
        case 7:
            return 0;
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl;
        }
    }

    return 0;
}
