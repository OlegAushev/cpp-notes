#include <iostream>
#include <memory>


struct A
{
	A() { std::cout << "A::A\n"; }
	virtual ~A() { std::cout << "A::~A\n"; }
	virtual void foo() { std::cout << "A::foo\n"; }
};

struct B : public A
{
	B() { std::cout << "B::B\n"; }
	virtual ~B() { std::cout << "B::~B\n"; }
	void foo() override { std::cout << "B::foo\n"; }
};

A* create()
{
	return new B;
}



int main()
{
	std::unique_ptr<A> ptr = std::make_unique<B>();
	ptr->foo();

	return 0;
}

