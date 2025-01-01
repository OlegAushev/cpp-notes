#include <ios>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

static int window_counter{0};

class Window {
private:
    int id_;
    std::string title_;
    std::vector<std::string> options_;
    bool fullscreen_{false};
    int border_{0};
public:
    Window(int id) : id_(id) {}
    void show() const {
        std::cout << "Window details:" << '\n'
                  << "Id:      " << id_ << '\n'
                  << "Title:   " << title_ << '\n'
                  << "Options:";
        if (options_.empty()) {
            std::cout << " none";
        }
        for (const auto& option : options_) {
            std::cout << ' ' << option;
        }

        std::cout << '\n'
                  << "F/s:     " << std::boolalpha << fullscreen_
                  << std::noboolalpha << '\n'
                  << "Border:  " << border_ << '\n';
    }

    void set_title(const std::string title) { title_ = title; }
    void add_option(const std::string option) { options_.emplace_back(option); }
    void toggle_fullscreen(bool v) { fullscreen_ = v; }
    void set_border(int v) { border_ = v; }
};

class WindowBuilder {
protected:
    std::unique_ptr<Window> window_;
public:
    WindowBuilder() : window_{std::make_unique<Window>(window_counter++)} {}
    std::unique_ptr<Window> build() {
        auto product = std::move(window_);
        window_ = std::make_unique<Window>(window_counter++);
        return product;
    }
    virtual WindowBuilder& title(const std::string& t) { return *this; }
    virtual WindowBuilder& options(const std::vector<std::string> opt) {
        return *this;
    }
    virtual WindowBuilder& fullscreen(bool v) { return *this; }
    virtual WindowBuilder& border(int v) { return *this; }
};

class StandardWindowBuilder : public WindowBuilder {
public:
    StandardWindowBuilder() = default;
    virtual WindowBuilder& title(const std::string& t) override {
        window_->set_title(t);
        return *this;
    }
    virtual WindowBuilder&
    options(const std::vector<std::string> opt) override {
        for (const auto& option : opt) {
            window_->add_option(option);
        }
        return *this;
    }
    virtual WindowBuilder& fullscreen(bool v) override {
        window_->toggle_fullscreen(v);
        return *this;
    }
    virtual WindowBuilder& border(int v) override {
        window_->set_border(v);
        return *this;
    }
};

class DecoratedWindowBuilder : public WindowBuilder {
public:
    DecoratedWindowBuilder() = default;
    virtual WindowBuilder& title(const std::string& t) override {
        const std::string decorated_title{"<<" + t + ">>"};
        window_->set_title(decorated_title);
        return *this;
    }
    virtual WindowBuilder&
    options(const std::vector<std::string> opt) override {
        for (const auto& option : opt) {
            window_->add_option(option);
        }
        return *this;
    }
    virtual WindowBuilder& fullscreen(bool v) override {
        window_->toggle_fullscreen(v);
        window_->add_option("decorated_fullscreen");
        return *this;
    }

    virtual WindowBuilder& border(int v) override {
        window_->set_border(v);
        window_->add_option("decorated_border");
        return *this;
    };
};

class WindowBuildDirector {
public:
    std::unique_ptr<Window> build_window(WindowBuilder& builder,
                                         const std::string& title) {
        return builder.title(title)
                .options({})
                .fullscreen(false)
                .border(0)
                .build();
    }

    std::unique_ptr<Window> build_fullscreen_window(WindowBuilder& builder,
                                                    const std::string& title) {
        return builder.title(title)
                .options({})
                .fullscreen(true)
                .border(0)
                .build();
    }
};

int main() {
    WindowBuildDirector director;
    StandardWindowBuilder standard_builder;

    auto win1 =
            director.build_fullscreen_window(standard_builder, "Main Window");
    auto win2 = director.build_window(standard_builder, "Tools");

    win1->show();
    win2->show();

    DecoratedWindowBuilder decorated_builder;
    auto win3 = director.build_window(decorated_builder, "Notifications");

    win3->show();

    return 0;
}
