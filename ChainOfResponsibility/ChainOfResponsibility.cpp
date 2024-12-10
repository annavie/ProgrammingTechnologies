#include <iostream>
#include <memory>
#include <string>
class SupportHandler {
protected:
    std::shared_ptr<SupportHandler> nextHandler;

public:
    virtual ~SupportHandler() = default;

    void setNextHandler(std::shared_ptr<SupportHandler> handler) {
        nextHandler = std::move(handler);
    }

    virtual void handleRequest(const std::string& issueType) {
        if (nextHandler) {
            nextHandler->handleRequest(issueType);
        } else {
            std::cout << "No handler available for the issue: " << issueType << "\n";
        }
    }
};
class TechnicalSupportHandler : public SupportHandler {
public:
    void handleRequest(const std::string& issueType) override {
        if (issueType == "Technical") {
            std::cout << "TechnicalSupportHandler: Resolving technical issue.\n";
        } else if (nextHandler) {
            nextHandler->handleRequest(issueType);
        }
    }
};
class BillingSupportHandler : public SupportHandler {
public:
    void handleRequest(const std::string& issueType) override {
        if (issueType == "Billing") {
            std::cout << "BillingSupportHandler: Resolving billing issue.\n";
        } else if (nextHandler) {
            nextHandler->handleRequest(issueType);
        }
    }
};

class GeneralSupportHandler : public SupportHandler {
public:
    void handleRequest(const std::string& issueType) override {
       std::cout << "Smth ..."  << std::endl;
    }
};

int main() {
    std::shared_ptr<SupportHandler> techSupport = std::make_shared<TechnicalSupportHandler>();
    std::shared_ptr<SupportHandler> billingSupport = std::make_shared<BillingSupportHandler>();
    std::shared_ptr<SupportHandler> generalSupport = std::make_shared<GeneralSupportHandler>();

    techSupport->setNextHandler(billingSupport);
    billingSupport->setNextHandler(generalSupport);

    techSupport->handleRequest("Technical");
    techSupport->handleRequest("Billing");
    techSupport->handleRequest("General");
    techSupport->handleRequest("Unknown");

    return 0;
}
