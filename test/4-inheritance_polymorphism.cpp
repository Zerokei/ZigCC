#include <iostream>

class Base
{
public:
	virtual void func() {
		std::cout << "Base!" << std::endl;
	}
public:
    void print() {
        std::cout << "a = " << a << std::endl;
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
private:
    int b;
};

int main()
{
    Base base;
    Derived derived;
    Base* p = new Derived;

    base.print();
	base.func();

    derived.print();
	derived.func();

    p->func();

	return 0;
}