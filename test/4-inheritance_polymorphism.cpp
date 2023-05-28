int printf(char *s, ...);

class Base
{
public:
	virtual void func() {
		printf("Base!\n");
	}
protected:
    int a;
private:
    int b;
};

class Derived : public Base
{
public:
	virtual void func() {
		printf("Derived!\n");
	}
private:
    int b;
};

int main()
{
    Base base;
    Derived derived;
    Base* p = new Derived;

	base.func();
	derived.func();
    p->func();

	return 0;
}