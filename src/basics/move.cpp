#include <iostream>

struct Foo {
    Foo() { std::cout << "Foo::Foo\n"; }
    Foo(const Foo&) { std::cout << "Foo::Copy Ctor!\n"; }
    ~Foo() { std::cout << "Foo::~Foo\n"; }
};

Foo createFoo() {
    Foo foo;
    Foo bar = foo;
    return bar;
}

[[gnu::weak]] int main() {
    Foo foo = createFoo();
    std::cout << "End of main() body.\n";

    return 0;
}
