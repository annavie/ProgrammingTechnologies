#include <iostream>
#include <string>

class TravelBooking {
public:
    void showBookingDetails() const {
        std::cout << "Travel Booking Details:" << std::endl;
        std::cout << "Class: " << travelClass << std::endl;
        std::cout << "Seat: " << (seatType.empty() ? "No preference" : seatType) << std::endl;
        std::cout << "Meal: " << (meal.empty() ? "No meal preference" : meal) << std::endl;
        std::cout << "Baggage: " << (extraBaggage ? "Included" : "Not included") << std::endl;
        std::cout << "Insurance: " << (insurance ? "Included" : "Not included") << std::endl;
    }
    friend class TravelBookingBuilder;

private:
    TravelBooking() = default;  

    std::string travelClass;
    std::string seatType;
    std::string meal;
    bool extraBaggage = false;
    bool insurance = false;
};

class TravelBookingBuilder {
public:
    TravelBookingBuilder(const std::string& travelClass) {
        booking.travelClass = travelClass;
    }

    TravelBookingBuilder& setSeatType(const std::string& seat) {
        booking.seatType = seat;
        return *this;
    }

    TravelBookingBuilder& setMeal(const std::string& mealPreference) {
        booking.meal = mealPreference;
        return *this;
    }

    TravelBookingBuilder& addBaggage() {
        booking.extraBaggage = true;
        return *this;
    }

    TravelBookingBuilder& addInsurance() {
        booking.insurance = true;
        return *this;
    }

    TravelBooking build() {
        return booking;
    }

private:
    TravelBooking booking; 
};

int main() {
    TravelBooking economyBooking = TravelBookingBuilder("Economy")
                                       .setSeatType("Window")
                                       .setMeal("Vegetarian")
                                       .addBaggage()
                                       .build();

    TravelBooking businessBooking = TravelBookingBuilder("Business")
                                        .setSeatType("Aisle")
                                        .setMeal("Gourmet")
                                        .addInsurance()
                                        .build();

    TravelBooking firstClassBooking = TravelBookingBuilder("First Class")
                                          .addInsurance()
                                          .build();

    std::cout << "Economy Booking: " << std::endl;
    economyBooking.showBookingDetails();

    std::cout << "\nBusiness Booking: " << std::endl;
    businessBooking.showBookingDetails();

    std::cout << "\nFirst Class Booking: " << std::endl;
    firstClassBooking.showBookingDetails();

    return 0;
}
