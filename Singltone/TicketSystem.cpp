#include<iostream>
#include<vector>
#include<mutex>


class TicketSystem{
public:
    static TicketSystem& getInstance(){
        static TicketSystem instance;
        return instance;
     };
     bool tryBooking(int seatNumber) {
        std::lock_guard<std::mutex> lock(m_mutex);    
      
        if (!isValidSeatNumber(seatNumber)) {
            throw std::out_of_range("Invalid seat number");
        }    TicketSystem& ticketSystem = TicketSystem::getInstance();


        if (isSeatBooked(seatNumber)) {
            std::cout << "Booking failed: Seat " << seatNumber << " is already booked!" << std::endl;
            return false; 
        }

        bookTicket(seatNumber);
        return true; 
        }
private:
    std::vector<bool> m_seats; 
    std::mutex m_mutex;
    TicketSystem(int numberofSeats = 10) : m_seats(numberofSeats, false){}
    TicketSystem(const TicketSystem&) = delete;
    TicketSystem& operator=(const TicketSystem) = delete;

    bool isValidSeatNumber(int seatNumber) const {
        return seatNumber >= 0 && seatNumber < m_seats.size();
    }
    bool isSeatBooked(int seatNumber) const {
        return m_seats[seatNumber];
    }
     void bookTicket(int seatNumber) {
        m_seats[seatNumber] = true; 
        std::cout << "Seat " << seatNumber << " successfully booked!" << std::endl;
    }

};

int main() {
    TicketSystem& ticketSystem = TicketSystem::getInstance();
    ticketSystem.tryBooking(3);
    ticketSystem.tryBooking(4);
    ticketSystem.tryBooking(1);
    ticketSystem.tryBooking(3);
return 0;
}