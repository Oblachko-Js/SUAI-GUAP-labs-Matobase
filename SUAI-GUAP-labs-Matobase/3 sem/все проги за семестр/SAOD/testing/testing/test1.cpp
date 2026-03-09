#include <iostream>
#include <conio.h>
#include <stack>
using namespace std;
int COUNT = 10;
struct Tree {
	int elem;
	int height;
	Tree* Prev;
	Tree* Left;
	Tree* Right;
};
void ShowTree(Tree* node);
void BalanceTree(Tree*& Root, Tree*& NewElem);
void AddTreeElem(Tree*& Root, Tree* NewElem);
void LeftRotate(Tree*& x);
void RightRotate(Tree*& y);
void BigLeftRotate(Tree*& node);
void BigRightRotate(Tree*& node);
void DeleteTreeElem(Tree*& Root, Tree*& DeleteElem);
Tree* SearchTreeElem(Tree* Root, int target);
void DisplayMenu();
int max(int a, int b) {
	return (a > b) ? a : b;
}
int GetHeight(Tree* node) {
	if (node == nullptr)
		return 0;
	return node->height;
}
void ShowTree(Tree* node) {
	if (node != nullptr) {
		// Traverse the left subtree
		ShowTree(node->Left);
		// Process the current node
		cout << node->elem << " ";
		// Traverse the right subtree
		ShowTree(node->Right);
	}
}
void BalanceTree(Tree*& Root, Tree*& NewElem) {
	Tree* MainTree = NewElem;
	while (true) {
		MainTree->height = max(GetHeight(MainTree->Left), GetHeight(MainTree -> Right)) + 1;
		int balance = GetHeight(MainTree->Right) - GetHeight(MainTree->Left);
		if (balance == 2) {
			if (GetHeight(MainTree->Right->Right) - GetHeight(MainTree -> Right->Left) == 0)
LeftRotate(MainTree);
			else if (GetHeight(MainTree->Right->Right) - GetHeight(MainTree -> Right->Left) == 1)
LeftRotate(MainTree);
			else
				BigLeftRotate(MainTree);
		}
		else if (balance == -2) {
			if (GetHeight(MainTree->Left->Right) - GetHeight(MainTree->Left -> Left) == 0)
RightRotate(MainTree);
			else if (GetHeight(MainTree->Left->Right) - GetHeight(MainTree -> Left->Left) == -1)
RightRotate(MainTree);
			else
				BigRightRotate(MainTree);
		}
		if (MainTree->Prev)
			MainTree = MainTree->Prev;
		else
			break;
	}
	Root = MainTree;
}
void AddTreeElem(Tree*& Root, Tree* NewElem) {
	Tree* MainTree = Root;
	if (!Root) {
		Root = new Tree;
		Root->elem = NewElem->elem;
		Root->height = 1;
		Root->Prev = nullptr;
		Root->Left = nullptr;
		Root->Right = nullptr;
		MainTree = Root;
	}
	else {
		while (true) {
			if (NewElem->elem < MainTree->elem) {
				if (MainTree->Left)
					MainTree = MainTree->Left;
				else {
					MainTree->Left = NewElem;
					NewElem->Prev = MainTree;
					break;
				}
			}
			else {
				if (MainTree->Right)
					MainTree = MainTree->Right;
				else {
					MainTree->Right = NewElem;
					NewElem->Prev = MainTree;
					break;
				}
			}
		}
		BalanceTree(Root, MainTree);
	}
}
void LeftRotate(Tree*& x) {
	Tree* y = x->Right;
	x->Right = y->Left;
	if (y->Left)
		y->Left->Prev = x;
	y->Prev = x->Prev;
	if (x->Prev) {
		if (x->Prev->Left == x)
			x->Prev->Left = y;
		else
			x->Prev->Right = y;
	}
	y->Left = x;
	x->Prev = y;
	x->height = max(GetHeight(x->Left), GetHeight(x->Right)) + 1;
	y->height = max(GetHeight(y->Left), GetHeight(y->Right)) + 1;
}
void RightRotate(Tree*& y) {
	Tree* x = y->Left;
	y->Left = x->Right;
	if (x->Right)
		x->Right->Prev = y;
	x->Prev = y->Prev;
	if (y->Prev) {
		if (y->Prev->Left == y)
			y->Prev->Left = x;
		else
			y->Prev->Right = x;
	}
	x->Right = y;
	y->Prev = x;
	y->height = max(GetHeight(y->Left), GetHeight(y->Right)) + 1;
	x->height = max(GetHeight(x->Left), GetHeight(x->Right)) + 1;
}
void BigLeftRotate(Tree*& node) {
	RightRotate(node->Right);
	LeftRotate(node);
}
void BigRightRotate(Tree*& node) {
	LeftRotate(node->Left);
	RightRotate(node);
}
// Implement BigLeftRotate, BigRightRotate, and ShowTree functions as needed.
void DeleteTreeElem(Tree*& Root, Tree*& DeleteElem)
{
	Tree* MainTree = Root;
	Tree* TmpElem = NULL;
	Tree* OneMoreTmp = NULL;
	int counter = 0;
	while (true)
	{
		if (MainTree)
		{
			if (DeleteElem->elem == MainTree->elem)
			{
				if (MainTree->Prev || GetHeight(MainTree) > 1)
				{
					OneMoreTmp = MainTree;
					if (MainTree->Left || MainTree->Right)
					{
						if (MainTree->Right)
							MainTree = MainTree->Right;
						TmpElem = OneMoreTmp->Prev;
						while (MainTree->Left)
							MainTree = MainTree->Left;
						if (MainTree->Prev)
						{
							if (MainTree->Prev->Right == MainTree)
								MainTree->Prev->Right = NULL;
							else
								MainTree->Prev->Left = NULL;
						}
						if (TmpElem)
						{
							if (TmpElem->Right)
							{
								if (TmpElem->Right == OneMoreTmp)
									TmpElem->Right = MainTree;
								else
									TmpElem->Left = MainTree;
							}
							else
								TmpElem->Left = MainTree;
						}
						if (MainTree->Prev != OneMoreTmp)
							TmpElem = MainTree->Prev;
						else TmpElem = MainTree;
						MainTree->Prev = OneMoreTmp->Prev;
						if (OneMoreTmp->Right != MainTree)
						{
							MainTree->Right = OneMoreTmp->Right;
							if (MainTree->Right)
								MainTree->Right->Prev = MainTree;
						}
						else
							MainTree->Right = NULL;
						if (OneMoreTmp->Left != MainTree)
						{
							MainTree->Left = OneMoreTmp->Left;
							if (MainTree->Left)
								MainTree->Left->Prev = MainTree;
						}
						else
							MainTree->Left = NULL;
						BalanceTree(Root, TmpElem);
					}
					else
					{
						TmpElem = MainTree->Prev;
						if (TmpElem)
						{
							if (TmpElem->Right)
							{
								if (TmpElem->Right == MainTree)
									TmpElem->Right = NULL;
								else
									TmpElem->Left = NULL;
							}
							else
								TmpElem->Left = NULL;
						}
						BalanceTree(Root, TmpElem);
					}
					cout << "элемент был удален" << endl;
					//ShowTree (Root);
					_getch();
					return;
				}
				else
				{
					Root = NULL;
					cout << "Дерево сейчас пусто" << endl;
					_getch();
					return;
				}
			}
			else if (DeleteElem->elem > MainTree->elem)
				MainTree = MainTree->Right;
			else
				MainTree = MainTree->Left;
		}
		else
		{
			cout << "Нет такого элемента в дереве!" << endl;
			_getch();
			return;
		}
	}
}
Tree* SearchTreeElem(Tree* Root, int target) {
	Tree* Current = Root;
	while (Current) {
		if (target == Current->elem)
			return Current;
		else if (target > Current->elem)
			Current = Current->Right;
		else
			Current = Current->Left;
	}
	return nullptr;
}
void PrintTree(Tree* node, string prefix = "", bool isLeft = true) {
	if (node != nullptr) {
		cout << (isLeft ? "L" : "R") << "[" << node->elem << "] (Level: " <<
			node->height << ")" << endl;
		string newPrefix = prefix + (isLeft ? " |" : " ");
		PrintTree(node->Left, newPrefix, true);
		PrintTree(node->Right, newPrefix, false);
	}
}
void print2DUtil(Tree* root, int space)
{
	// Base case
	if (root == nullptr)
		return;
	// Increase distance between levels
	space += COUNT;
	// Process right child first
	print2DUtil(root->Right, space);
	// Print current node after space count
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->elem << "\n";
	// Process left child
	print2DUtil(root->Left, space);
}
void print2DUt(Tree* root, int space)
{
	// Base case
	if (root == nullptr)
		return;
	// Increase distance between levels
	space += COUNT;
	// Process right child first
	print2DUt(root->Right, space);
	// Print current node after space count
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->elem;
	// Add arrows to point from parent to children
	if (root->Left != nullptr || root->Right != nullptr) {
		cout << " --> ";
		if (root->Left != nullptr)
			cout << "(" << root->Left->elem;
		if (root->Left != nullptr && root->Right != nullptr)
			cout << ", ";
		if (root->Right != nullptr)
			cout << root->Right->elem;
		cout << ")";
	}
	cout << "\n";
	// Process left child
	print2DUt(root->Left, space);
}
// Wrapper over print2DUtil()
void print2D(Tree* root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}
void print2(Tree* root)
{
	// Pass initial space count as 0
	print2DUt(root, 0);
}
void ListDescendants(Tree* node) {
	if (node != nullptr) {
		// Сначала обойдем левое поддерево
		ListDescendants(node->Left);
		// Затем выведем список потомков данного узла
		cout << "Потомки узла " << node->elem << ": ";
		if (node->Left != nullptr) {
			cout << node->Left->elem << " ";
		}
		if (node->Right != nullptr) {
			cout << node->Right->elem << " ";
		}
		cout << endl;
		// Потом обойдем правое поддерево
		ListDescendants(node->Right);
	}
}
void DisplayMenu() {
	cout << "Древовидное меню АВЛ:" << endl;
	cout << "1. Добавить элемент" << endl;
	cout << "2. Поиск элемента" << endl;
	cout << "3. Удалить элемент" << endl;
	cout << "4. Отобразите дерево по в виде списка" << endl;
	cout << "5. Отобразите дерево на чертеже" << endl;
	cout << "6. Для каждого узла дерева" << endl;
	cout << "7. Выход" << endl;
}
#include "try.h"
int main() {
	system("color f1");
	setlocale(LC_ALL, "Russian");
	Tree* Root = nullptr;
	Tree* newNode = nullptr;
	Tree* foundNode = nullptr;
	int i, counter = 0;
	int choice;
	do {
		DisplayMenu();
		cout << "Введите свой выбор: ";
		cin >> choice;
		switch (choice) {
		case 1:
			int numValues;
			cout << "Введите количество значений: ";
			cin >> numValues;
			for (int i = 0; i < numValues; i++) {
				int value;
				// You can modify this part to get values from the user or any other source
					cout << "Введите значение " << (i + 1) << ": ";
				cin >> value;
				foundNode = SearchTreeElem(Root, value);
				if (foundNode) {
					cout << "Элемент " << value << " уже находится в дереве.Дублирование не допускается." << endl;
				}
				else {
					// Create a new node and add it to the tree
					newNode = new Tree;
					newNode->elem = value;
					newNode->height = 1;
					newNode->Prev = nullptr;
					newNode->Left = nullptr;
					newNode->Right = nullptr;
					AddTreeElem(Root, newNode);
				}
			}
			break;
		case 2:
			int target;
			cout << "Введите значение для поиска: ";
			cin >> target;
			// Search for the element
			foundNode = SearchTreeElem(Root, target);
			if (foundNode) {
				cout << "Элемент " << target << " найдено в дереве" <<
					endl;
			}
			else {
				cout << "Элемент " << target << " не найден на дереве." <<
					endl;
			}
			break;
		case 3:
			int deleteValue;
			cout << "Введите значение для удаления: ";
			cin >> deleteValue;
			// Search for the element and delete it
			foundNode = SearchTreeElem(Root, deleteValue); // Reuse
				if (foundNode) {
					DeleteTreeElem(Root, foundNode);
				}
				else {
					cout << "Элемент " << deleteValue << " не найдено в дереве. Удаление завершилось неудачей." << endl;
				}
			break;
		case 4:
			cout << "В Симметричный обхода : ";
			ShowTree(Root);
			cout << endl;
			break;
		case 5:
			cout << "введите 1, чтобы показать общее дерево, или 2, чтобы показать подробное : ";
				cin >> i;
			if (i == 1) {
				print2D(Root);
			}
			else if (i == 2) {
				print2(Root);
			}
			else {
				cout << "Недопустимый параметр";
			}
			break; // Add this break statement
		case 6:
			ListDescendants(Root);
			break;
		case 7:
			break;
		default:
			cout << "Неверный выбор. Пожалуйста, введите допустимый вариант." << endl;
				break;
		}
		// Wait for user input before clearing the screen
		cout << "Нажмите любую клавишу, чтобы продолжить...";
		_getch();
		system("cls"); // Clear the screen (for Windows)
	} while (choice != 7);
	delete newNode;
	return 0;
}