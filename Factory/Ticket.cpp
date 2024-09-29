#include<iostream>
#include<string>

class Ticket{
public:
    virtual void displayDetails() = 0; 

};
class StandardTicket : public Ticket {
public: 
    void displayDetails() override{
        std::cout << "Standard Ticket." << std::endl;

    }
};
class VIPTicket : public Ticket{
public:
    void displayDetails() override{
        std::cout << "VIP Ticket." << std::endl;

    }
};
class StudentTicket : public Ticket{
public:
    void displayDetails() override{
        std::cout << "Student Ticket." << std::endl;

    }
};
class TicketFactory{
public:
    static Ticket* createTicket(std::string type){
        if (type == "Standard") {
            return new StandardTicket();
        } else if (type == "VIP") {
            return new VIPTicket();
        } else if (type == "Student") {
            return new StudentTicket();
        }
        return nullptr; 
    }
    
};

int main() {
    Ticket* ticket1 = TicketFactory::createTicket("VIP");
    ticket1->displayDetails();

    Ticket* ticket2 = TicketFactory::createTicket("Standard");
    ticket2->displayDetails(); 

    delete ticket1;
    delete ticket2;

    return 0;
}
