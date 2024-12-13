#include <iostream>
#include <string>

class Notifier {
public:
    virtual void sendNotification(const std::string& message) = 0;
    virtual ~Notifier() = default;
};

class EmailNotifier : public Notifier {
public:
    void sendNotification(const std::string& message) override {
        std::cout << "Sending Email: " << message << std::endl;
    }
};

class NotifierDecorator : public Notifier {
protected:
    Notifier* wrappedNotifier; 

public:
    explicit NotifierDecorator(Notifier* notifier) : wrappedNotifier(notifier) {}

    void sendNotification(const std::string& message) override {
        wrappedNotifier->sendNotification(message); 
    }

    virtual ~NotifierDecorator() = default;
};

class SMSNotifier : public NotifierDecorator {
public:
    explicit SMSNotifier(Notifier* notifier) : NotifierDecorator(notifier) {}

    void sendNotification(const std::string& message) override {
        NotifierDecorator::sendNotification(message); 
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

class SlackNotifier : public NotifierDecorator {
public:
    explicit SlackNotifier(Notifier* notifier) : NotifierDecorator(notifier) {}

    void sendNotification(const std::string& message) override {
        NotifierDecorator::sendNotification(message); 
        std::cout << "Sending Slack message: " << message << std::endl;
    }
};

int main() {
    Notifier* emailNotifier = new EmailNotifier();
    Notifier* smsNotifier = new SMSNotifier(emailNotifier);
    Notifier* slackNotifier = new SlackNotifier(smsNotifier);
    
    slackNotifier->sendNotification("Critical System Alert!");

    delete slackNotifier; 
    delete smsNotifier;
    delete emailNotifier;

    return 0;
}
