#include <iostream>
#include <vector>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class AirConditioner {
public:
    void turnOn() {
        std::cout << "Air Conditioner is ON" << std::endl;
    }

    void turnOff() {
        std::cout << "Air Conditioner is OFF" << std::endl;
    }

    void setTemperature(int temp) {
        std::cout << "Setting temperature to " << temp << " degrees" << std::endl;
    }

};
class TurnOnCommand : public Command {
private:
    AirConditioner& ac;
public:
    TurnOnCommand(AirConditioner& ac) : ac(ac) {}
    
    void execute() override {
        ac.turnOn();
    }
};
class TurnOffCommand : public Command {
private:
    AirConditioner& ac;
public:
    TurnOffCommand(AirConditioner& ac) : ac(ac) {}
    
    void execute() override {
        ac.turnOff();
    }
};
class SetTemperatureCommand : public Command {
private:
    AirConditioner& ac;
    int temp;
public:
    SetTemperatureCommand(AirConditioner& ac, int temp) : ac(ac), temp(temp) {}
    
    void execute() override {
        ac.setTemperature(temp);
    }
};

class RemoteControl {
private:
    Command* command;
public:
    void setCommand(Command* cmd) {
        command = cmd;
    }
    
    void pressButton() {
        if (command) {
            command->execute();
        }
    }
};

int main() {
    AirConditioner ac;
    TurnOnCommand turnOn(ac);
    TurnOffCommand turnOff(ac);
    SetTemperatureCommand setTemp(ac, 22);
    RemoteControl remote;
    
    remote.setCommand(&turnOn);
    remote.pressButton();
    
    remote.setCommand(&setTemp);
    remote.pressButton();  
    
    remote.setCommand(&turnOff);
    remote.pressButton();  
    
    return 0;
}
