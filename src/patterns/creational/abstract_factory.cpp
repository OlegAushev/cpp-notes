#include <iostream>
#include <memory>

class Button {
public:
    virtual ~Button() = default;
    virtual void press() = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void toggle() = 0;
};

class QtButton : public Button {
public:
    virtual ~QtButton() = default;
    virtual void press() override {
        std::cout << "QtButton pressed." << std::endl;
    }
};

class GtkButton : public Button {
public:
    virtual ~GtkButton() = default;
    virtual void press() override {
        std::cout << "GtkButton pressed." << std::endl;
    }
};

class QtCheckbox : public Checkbox {
public:
    virtual ~QtCheckbox() = default;
    virtual void toggle() override {
        std::cout << "QtCheckbox toggled." << std::endl;
    }
};

class GtkCheckbox : public Checkbox {
public:
    virtual ~GtkCheckbox() = default;
    virtual void toggle() override {
        std::cout << "GtkCheckbox toggled." << std::endl;
    }
};

class GuiFactory {
public:
    virtual ~GuiFactory() = default;
    virtual std::unique_ptr<Button> create_button() = 0;
    virtual std::unique_ptr<Checkbox> create_checkbox() = 0;
};

class QtFactory : public GuiFactory {
public:
    virtual ~QtFactory() = default;

    virtual std::unique_ptr<Button> create_button() override {
        return std::make_unique<QtButton>();
    }

    virtual std::unique_ptr<Checkbox> create_checkbox() override {
        return std::make_unique<QtCheckbox>();
    }
};

class GtkFactory : public GuiFactory {
public:
    virtual ~GtkFactory() = default;

    virtual std::unique_ptr<Button> create_button() override {
        return std::make_unique<GtkButton>();
    }

    virtual std::unique_ptr<Checkbox> create_checkbox() override {
        return std::make_unique<GtkCheckbox>();
    }
};


int main() {
    QtFactory qt_factory;
    auto button1 = qt_factory.create_button();
    auto checkbox1 = qt_factory.create_checkbox();
    button1->press();
    checkbox1->toggle();

    GtkFactory gtk_factory;
    auto button2 = gtk_factory.create_button();
    auto checkbox2 = gtk_factory.create_checkbox();
    button2->press();
    checkbox2->toggle();

    return 0;
}
