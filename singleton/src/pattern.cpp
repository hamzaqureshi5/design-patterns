#include <iostream>
#include <mutex>

class Singleton {
private:
    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Optional: Delete move operations too
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    // Static instance pointer
    static Singleton* instance;
    static std::mutex mtx;

public:
    // Static method to access the single instance
    static Singleton& getInstance() {
        // Double-checked locking for thread-safe lazy initialization
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return *instance;
    }

    // Example method
    void showMessage() const {
        std::cout << "Hello from Singleton instance!\n";
    }
};

// Static member initialization
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

// ---------- Example Usage ----------
int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();

    s1.showMessage();

    // Check if both instances are the same
    if (&s1 == &s2) {
        std::cout << "Both are the same instance.\n";
    }

    return 0;
}
