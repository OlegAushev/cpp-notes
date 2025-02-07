#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

struct Base {
    Base() { std::cout << "Base::Base\n"; }
    virtual ~Base() { std::cout << "Base::~Base\n"; }
    virtual void foo() { std::cout << "Base::foo\n"; }
};

struct Derived : public Base {
    Derived() { std::cout << "Derived::Derived\n"; }
    ~Derived() { std::cout << "Derived::~Derived\n"; }
    virtual void foo() override { std::cout << "Derived::foo\n"; }
};

void thr(std::shared_ptr<Base> p) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p;
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "	lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}

Derived* createDerived() { return new Derived; }

/**
 * @brief
 *
 * @return int
 */
[[gnu::weak]] int main(int, char**) {
    std::shared_ptr<Base> p = std::make_shared<Derived>();

    std::shared_ptr<Base> p2(createDerived());

    std::cout << "Created a shared Derived (as a pointer to Base):\n"
              << "	p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';

    std::thread t1(thr, p), t2(thr, p), t3(thr, p);

    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << " 	p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join();
    t2.join();
    t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";

    return 0;
}
