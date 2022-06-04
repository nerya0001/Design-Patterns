#include "singleton.hpp"

class TestSingleton {

private:
    int value;

public:
    TestSingleton() {
        this->value = 0;
    }

    void setValue(int x) {
        this->value = x;
    }

    int getValue() const {
        return this->value;
    }

};


int main() {
    // the test should print '2' twice because they are the same instance.
    auto instance1 = singleton<TestSingleton>::getInstance();
    auto instance2 = singleton<TestSingleton>::getInstance();
    instance1->setValue(2);
    std::cout << instance1->getValue() << "\n";
    std::cout << instance2->getValue() << "\n";


}
