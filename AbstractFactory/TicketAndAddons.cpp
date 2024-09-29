#include<iostream>
#include<string>

class Ticket{
public:
    virtual std::string getDescription() const = 0;
    virtual double getPrice() const = 0;
    virtual ~Ticket() = default;

};
class Addon{
public:
    virtual std::string getDescription() const = 0;
    virtual double getPrice() const = 0;
    virtual ~Addon() = default;
};

class StandardTicket : public Ticket {
public:
    std::string getDescription() const override {
        return "Standard Ticket";
    }

    double getPrice() const override {
        return 20.0; 
    }
};

class VIPTicket : public Ticket {
public:
    std::string getDescription() const override {
        return "VIP Ticket";
    }

    double getPrice() const override {
        return 50.0; 
}
};
class FoodAddOn : public Addon {
public:
    std::string getDescription() const override {
        return "Food Package";
    }

    double getPrice() const override {
        return 10.0; 
    }
};
class MerchandiseAddOn : public Addon {
public:
    std::string getDescription() const override {
        return "Merchandise Package";
    }

    double getPrice() const override {
        return 15.0; 
    }
};

class BookingFactory{
public:
    virtual Ticket* createTicket() const = 0;
    virtual Addon* createAddon() const = 0;
    virtual ~BookingFactory() = default;

};

class StandartTicketFactory : public BookingFactory{
public:
    Ticket* createTicket() const override {
        return new StandardTicket();
    }

    Addon* createAddon() const override {
        return new FoodAddOn(); 
    }

};
class VIPTicketFactory : public BookingFactory {
public:
    Ticket* createTicket() const override {
        return new VIPTicket();
    }

    Addon* createAddon() const override {
        return new MerchandiseAddOn(); 
    }
};
void bookTicket(const BookingFactory& factory) {
    Ticket* ticket = factory.createTicket();
    Addon* addon = factory.createAddon();

    std::cout << "Booking: " << ticket->getDescription() << " with " << addon->getDescription() << std::endl;
    std::cout << "Total Price: $" << (ticket->getPrice() + addon->getPrice()) << std::endl;

    delete ticket;
    delete addon;
}

int main() {
    StandartTicketFactory standardFactory;
    bookTicket(standardFactory);
    VIPTicketFactory vipFactory;
    bookTicket(vipFactory);
    return 0;
}