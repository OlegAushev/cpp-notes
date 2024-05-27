#include <iostream>
#include <memory>


class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual std::string name() const = 0;
};


class ConcreteProductAX : public AbstractProductA {
public:
virtual ~ConcreteProductAX() = default;
    virtual std::string name() const override { return "A-X"; }
};


class ConcreteProductAY : public AbstractProductA {
public:
    virtual ~ConcreteProductAY() = default;
    virtual std::string name() const override { return "A-Y"; }
};


class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual std::string name() const = 0;
};


class ConcreteProductBX : public AbstractProductB {
public:
virtual ~ConcreteProductBX() = default;
    virtual std::string name() const override { return "B-X"; }
};


class ConcreteProductBY : public AbstractProductB {
public:
    virtual ~ConcreteProductBY() = default;
    virtual std::string name() const override { return "B-Y"; }
};




class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> create_product_a() = 0;
    virtual std::unique_ptr<AbstractProductB> create_product_b() = 0;
};


class ConcreteFactoryX : public AbstractFactory {
public:
    virtual ~ConcreteFactoryX() = default;
    virtual std::unique_ptr<AbstractProductA> create_product_a() override { return std::make_unique<ConcreteProductAX>(); }
    virtual std::unique_ptr<AbstractProductB> create_product_b() override { return std::make_unique<ConcreteProductBX>(); }
};


class ConcreteFactoryY : public AbstractFactory {
public:
    virtual ~ConcreteFactoryY() = default;
    virtual std::unique_ptr<AbstractProductA> create_product_a() override { return std::make_unique<ConcreteProductAY>(); }
    virtual std::unique_ptr<AbstractProductB> create_product_b() override { return std::make_unique<ConcreteProductBY>(); }
};




int main() {
    ConcreteFactoryX factory_x;
    ConcreteFactoryY factory_y;

    auto p_ax = factory_x.create_product_a();
    auto p_bx = factory_x.create_product_b();
    auto p_ay = factory_y.create_product_a();
    auto p_by = factory_y.create_product_b();

    std::cout << p_ax->name() << '\n';
    std::cout << p_bx->name() << '\n';
    std::cout << p_ay->name() << '\n';
    std::cout << p_by->name() << '\n';

    return 0;
}
