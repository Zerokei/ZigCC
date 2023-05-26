#include <iostream>

class Base
{
public:
	virtual void func() {
		std::cout << "Base!" << std::endl;
	}
public:
    Base() : a(0), b(0) {}
    Base(int a, int b) : a(a), b(b) {}
    Base(const Base &base) : a(base.a), b(base.b) {}
    ~Base() {}
public:
    void print() {
        std::cout << a << " " << b << std::endl;
    }
protected:
    int a;
private:
    int b;
};
class Derived :public Base
{
public:
	virtual void func() {
		std::cout << "Derived!" << std::endl;
	}
public:
    Derived() : Base(), b(0) {}
    Derived(int a, int b) : Base(a, b), b(b) {}
    Derived(const Derived &derived) : Base(derived), b(derived.b) {}
    ~Derived() {}
private:
    int b;
};

int main()
{
    Base base(1, 2);
    Derived derived;

    base.print();
	base.func();

    derived.print();
	derived.func();
	return 0;
}