#include <iostream>

struct Node {
    int coefficient;
    int exponent;
    Node* next;
};

class PolynomialList {
private:
    Node* head;
public:
    PolynomialList() {
        head = NULL;
    }

    void addTerm(int coefficient, int exponent) {
        Node* newNode = new Node;
        newNode->coefficient = coefficient;
        newNode->exponent = exponent;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeTerm(int exponent) {
        if (head == NULL) {
            return;
        }
        else if (head->exponent == exponent) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* prev = head;
            Node* curr = head->next;
            while (curr != NULL) {
                if (curr->exponent == exponent) {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void removeZeroCoefficients() {
        Node* prev = NULL;
        Node* curr = head;

        while (curr != NULL) {
            if (curr->coefficient == 0 || (curr->coefficient == 0 && curr->exponent == 0)) {
                if (prev == NULL) {
                    head = curr->next;
                    delete curr;
                    curr = head;
                }
                else {
                    prev->next = curr->next;
                    delete curr;
                    curr = prev->next;
                }
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void displayPolynomial() {
        if (head == NULL) {
            std::cout << "Многочлен пуст." << std::endl;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                std::cout << temp->coefficient << "x^" << temp->exponent;
                if (temp->next != NULL) {
                    std::cout << " + ";
                }
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

    void derivative() {
        if (head == NULL) {
            std::cout << "Многочлен пуст." << std::endl;
        }
        else {
            Node* prev = NULL;
            Node* curr = head;
            while (curr != NULL) {
                curr->coefficient *= curr->exponent;
                curr->exponent--;
                if (curr->coefficient == 0) {
                    // Если коэффициент стал нулевым, удаляем этот член
                    if (prev == NULL) {
                        head = curr->next;
                        delete curr;
                        curr = head;
                    }
                    else {
                        prev->next = curr->next;
                        delete curr;
                        curr = prev->next;
                    }
                }
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }

};

int main() {
    setlocale(LC_ALL, "Russian");
    system("color F0");
    std::cout << "Программа создана Борщем Н.С." << std::endl;
    int coefficient, exponent;
    PolynomialList polynomial;
    std::cout << "Введите полиномиальные члены (коэффициент и показатель степени):" << std::endl;
    std::cout << "(Введите коэффициент равный 0, чтобы прекратить добавление членов)" << std::endl;
    do {
        std::cout << "Коэффициент: ";
        std::cin >> coefficient;
        if (coefficient == 0) {
            break;
        }
        std::cout << "Экспонента: ";
        std::cin >> exponent;
        polynomial.addTerm(coefficient, exponent);
    } while (true);
    std::cout << "Оригинальный многочлен: ";
    polynomial.displayPolynomial();
    polynomial.derivative();
    std::cout << "Производная многочлена: ";
    polynomial.displayPolynomial();
    polynomial.removeZeroCoefficients();
    return 0;
}
