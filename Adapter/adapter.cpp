#include <iostream>

class Target {
public:
    virtual ~Target() = default;
    virtual void request() const {
        std::cout << "Target: Default behavior.\n";
    }
};

class Adaptee {
public:
    void specificRequest() const {
        std::cout << "Adaptee: Specific behavior.\n";
    }
};

class Adapter : public Target {
public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
    void request() const override {
        adaptee_->specificRequest();
    }

private:
    Adaptee* adaptee_;
};

int main() {
    Adaptee adaptee;
    Adapter adapter(&adaptee);
    std::cout << "Client: I can work with the Adapter:\n";
    adapter.request();

    return 0;
}
