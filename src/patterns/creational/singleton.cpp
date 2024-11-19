#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// Non-thread-safe Singleton
class SingletonNonSafe {
protected:
    SingletonNonSafe(const std::string& str) : _str(str) {}
    static inline SingletonNonSafe* _instance;
    std::string _str;

public:
    static SingletonNonSafe* instance(const std::string& str) {
        if (_instance == nullptr) {
            _instance = new SingletonNonSafe(str);
        }
        return _instance;
    }

    std::string str() const { return _str; }

    SingletonNonSafe(SingletonNonSafe const&) = delete;
    SingletonNonSafe(SingletonNonSafe&&) = delete;
    SingletonNonSafe& operator=(SingletonNonSafe const&) = delete;
    SingletonNonSafe& operator=(SingletonNonSafe&&) = delete;

    static void ThreadFoo() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        SingletonNonSafe* singleton = SingletonNonSafe::instance("FOO");
        std::cout << singleton->str() << "\n";
    }

    static void ThreadBar() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        SingletonNonSafe* singleton = SingletonNonSafe::instance("BAR");
        std::cout << singleton->str() << "\n";
    }
};

// Thread-safe Singleton
class SingletonSafe {
protected:
    SingletonSafe(const std::string& str) : _str(str) {}
    static inline SingletonSafe* _instance;
    std::string _str;
    static inline std::mutex _mutex;

public:
    static SingletonSafe* instance(const std::string& str) {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_instance == nullptr) {
            _instance = new SingletonSafe(str);
        }
        return _instance;
    }

    std::string str() const { return _str; }

    SingletonSafe(SingletonSafe const&) = delete;
    SingletonSafe(SingletonSafe&&) = delete;
    SingletonSafe& operator=(SingletonSafe const&) = delete;
    SingletonSafe& operator=(SingletonSafe&&) = delete;

    static void ThreadFoo() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        SingletonSafe* singleton = SingletonSafe::instance("FOO");
        std::cout << singleton->str() << "\n";
    }

    static void ThreadBar() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        SingletonSafe* singleton = SingletonSafe::instance("BAR");
        std::cout << singleton->str() << "\n";
    }
};

// Thread-safe Singleton C++11
class SingletonC11 {
protected:
    SingletonC11(const std::string& str) : _str(str) {}
    std::string _str;

public:
    static SingletonC11& instance(const std::string& str) {
        static SingletonC11 s(str);
        return s;
    }

    std::string str() const { return _str; }

    SingletonC11(SingletonC11 const&) = delete;
    SingletonC11(SingletonC11&&) = delete;
    SingletonC11& operator=(SingletonC11 const&) = delete;
    SingletonC11& operator=(SingletonC11&&) = delete;

    static void ThreadFoo() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << SingletonC11::instance("FOO").str() << "\n";
    }

    static void ThreadBar() {
        // emulating slow initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << SingletonC11::instance("BAR").str() << "\n";
    }
};

/**
 * @brief
 *
 * @return int
 */
int main(int, char**) {
    std::cout
            << "If you see the same value, then singleton was reused (ok)\n"
            << "If you see different values, then 2 singletons were created (bad)\n\n"
            << "Result for SingletonNonSafe:\n";
    std::thread t1(SingletonNonSafe::ThreadFoo);
    std::thread t2(SingletonNonSafe::ThreadBar);
    t1.join();
    t2.join();

    std::cout << "\nResult for  SingletonSafe:\n";
    std::thread t3(SingletonSafe::ThreadFoo);
    std::thread t4(SingletonSafe::ThreadBar);
    t3.join();
    t4.join();

    std::cout << "\nResult for  SingletonC11:\n";
    std::thread t5(SingletonC11::ThreadFoo);
    std::thread t6(SingletonC11::ThreadBar);
    t5.join();
    t6.join();

    return 0;
}
