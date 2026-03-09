//лаба 6, вариант 6
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

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
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

    void reverseInorderTraversal(TreeNode* node, std::vector<int>& result) {
        if (node == nullptr)
            return;
        reverseInorderTraversal(node->right, result);
        result.push_back(node->data);
        reverseInorderTraversal(node->left, result);
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

    double calculateAverageLeafValue(TreeNode* node, int& count, int& sum) {
        if (node == nullptr)
            return 0.0;

        if (node->left == nullptr && node->right == nullptr) {
            sum += node->data;
            count++;
        }

        double leftSum = calculateAverageLeafValue(node->left, count, sum);
        double rightSum = calculateAverageLeafValue(node->right, count, sum);

        return node->data + leftSum + rightSum;
    }

    void subtractValueFromLeaves(TreeNode* node, double value) {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr) {
            node->data -= value;
        }

        subtractValueFromLeaves(node->left, value);
        subtractValueFromLeaves(node->right, value);
    }

    TreeNode* removeDivisibleBy3(TreeNode* node) {
        if (node == nullptr)
            return nullptr;

        if (node->data % 3 == 0)
            return removeDivisibleBy3(node->left);

        node->left = removeDivisibleBy3(node->left);
        node->right = removeDivisibleBy3(node->right);

        return node;
    }

public:
    BalancedBST() : root(nullptr) {}

    void insert(int val) {
        std::vector<int> sortedElements;
        preorderTraversal(root, sortedElements);
        sortedElements.push_back(val);
        std::sort(sortedElements.begin(), sortedElements.end());
        root = sortedArrayToBST(sortedElements, 0, sortedElements.size() - 1);
    }

    void remove(int val) {
        bool balanceNeeded = false; // Создание переменной для передачи в функцию remove
        root = remove(root, val, balanceNeeded);
        if (balanceNeeded) {
            std::vector<int> sortedElements;
            preorderTraversal(root, sortedElements);
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

    std::vector<int> reverseInorderTraversal() {
        std::vector<int> result;
        reverseInorderTraversal(root, result);
        return result;
    }

    void processTree() {
        int leafCount = 0;
        int leafSum = 0;
        double averageLeafValue = calculateAverageLeafValue(root, leafCount, leafSum);

        if (leafCount > 0) {
            averageLeafValue /= leafCount;
            subtractValueFromLeaves(root, averageLeafValue);
        }

        root = removeDivisibleBy3(root);
        std::vector<int> sortedElements = reverseInorderTraversal();
        root = balanceTree(sortedElements, 0, sortedElements.size() - 1); // Балансировка после обработки дерева
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
        std::cout << "5. Обратный обход вершин" << std::endl;
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
            std::cout << "Обратный обход вершин: ";
            for (int val : tree.reverseInorderTraversal())
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
