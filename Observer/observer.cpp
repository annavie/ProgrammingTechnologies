#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

class Subscriber {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Subscriber() = default;
};

class iPhoneStore {
private:
    std::vector<Subscriber*> subscribers;

public:
    void attach(Subscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void detach(Subscriber* subscriber) {
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
    }

    void notify(const std::string& message) {
        for (Subscriber* subscriber : subscribers) {
            subscriber->update(message);
        }
    }

    void newiPhoneArrival(const std::string& model) {
        std::cout << "iPhone Store: New iPhone model available: " << model << std::endl;
        notify("New iPhone model: " + model + " is now available!");
    }
};
class Customer : public Subscriber {
private:
    std::string name;

public:
    Customer(const std::string& customerName) : name(customerName) {}

    void update(const std::string& message) override {
        std::cout << "Customer " << name << " received notification: " << message << std::endl;
    }
};
int main() {
    iPhoneStore store;

    Customer alice("Alice");
    Customer bob("Bob");

    store.attach(&alice);
    store.attach(&bob);

    store.newiPhoneArrival("iPhone 16");
    store.newiPhoneArrival("iPhone 16 Pro");

    store.detach(&bob);

    store.newiPhoneArrival("iPhone 16 Pro Max");

    return 0;
}
