#include <iostream>

class A {
public:
    A() {
        std::cout << getName();
    }

    virtual const char* getName() {
        return "A";
    }
};

class B : public A {
public:
    virtual const char* getName() {
        return "B";
    }
};

class C : public B {
public:
    virtual const char* getName() {
        return "C";
    }
};

class D : public C {
public:
    virtual const char* getName() {
        return "D";
    }
};

int main() {
    D d;
    std::cin.get();
    return 0;
}
