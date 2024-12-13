#include <iostream>
#include <string>

class Phone;

class State {
public:
    virtual void lock(Phone* phone) = 0;
    virtual void unlock(Phone* phone) = 0;
    virtual void ring(Phone* phone) = 0;
    virtual ~State() = default;
};
class Phone {
private:
    State* currentState;

public:
    explicit Phone(State* initialState) : currentState(initialState) {}

    void setState(State* state) {
        currentState = state;
    }

    void lock() {
        currentState->lock(this);
    }

    void unlock() {
        currentState->unlock(this);
    }

    void ring() {
        currentState->ring(this);
    }
};

class LockedState : public State {
public:
    void lock(Phone* phone) override {
        std::cout << "Phone is already locked." << std::endl;
    }

    void unlock(Phone* phone) override {
        std::cout << "Unlocking the phone..." << std::endl;
        phone->setState(new UnlockedState());
    }

    void ring(Phone* phone) override {
        std::cout << "Phone is ringing while locked!" << std::endl;
        phone->setState(new RingingState());
    }
};
class UnlockedState : public State {
public:
    void lock(Phone* phone) override {
        std::cout << "Locking the phone..." << std::endl;
        phone->setState(new LockedState());
    }

    void unlock(Phone* phone) override {
        std::cout << "Phone is already unlocked." << std::endl;
    }

    void ring(Phone* phone) override {
        std::cout << "Phone is ringing while unlocked!" << std::endl;
        phone->setState(new RingingState());
    }
};
class RingingState : public State {
public:
    void lock(Phone* phone) override {
        std::cout << "Can't lock the phone while it's ringing!" << std::endl;
    }

    void unlock(Phone* phone) override {
        std::cout << "Can't unlock the phone while it's ringing!" << std::endl;
    }

    void ring(Phone* phone) override {
        std::cout << "Phone is already ringing." << std::endl;
    }
};

int main() {
    Phone phone(new LockedState());

    phone.lock();   
    phone.unlock(); 
    phone.lock();   

    return 0;
}
