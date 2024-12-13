#include <iostream>
#include <string>

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player is on.\n"; }
    void off() { std::cout << "DVD Player is off.\n"; }
    void play(const std::string& movie) { std::cout << "Playing movie: " << movie << ".\n"; }
    void stop() { std::cout << "Stopped the movie.\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector is on.\n"; }
    void off() { std::cout << "Projector is off.\n"; }
    void setInput(const std::string& input) { std::cout << "Projector input set to " << input << ".\n"; }
};

class HomeTheaterFacade {
private:
    DVDPlayer* dvd;
    Projector* projector;

public:
    HomeTheaterFacade( DVDPlayer* d, Projector* p)
        : dvd(d), projector(p) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Preparing to watch a movie...\n";
        dvd->on();
        dvd->play(movie);
        projector->on();
        projector->setInput("DVD");
        std::cout << "Movie is now playing!\n";
    }

    void endMovie() {
        std::cout << "Shutting down the home theater system...\n";
        dvd->stop();
        dvd->off();
        projector->off();
        std::cout << "Home theater system is off.\n";
    }
};

int main() {
    DVDPlayer dvd;
    Projector projector;
    HomeTheaterFacade homeTheater(&dvd, &projector);
    homeTheater.watchMovie("Inception");
    std::cout << "\n... After the movie ends ...\n\n";
    homeTheater.endMovie();

    return 0;
}
