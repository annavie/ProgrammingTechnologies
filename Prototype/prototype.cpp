#include <iostream>
#include <memory>
#include <unordered_map>

class Shape {
public:
    virtual ~Shape() {}
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    Circle(int radius) : radius_(radius) {}
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    void draw() const override {
        std::cout << "Drawing a circle with radius: " << radius_ << std::endl;
    }

private:
    int radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(int width, int height) : width_(width), height_(height) {}
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
    void draw() const override {
        std::cout << "Drawing a rectangle with width: " << width_
                  << " and height: " << height_ << std::endl;
    }

private:
    int width_;
    int height_;
};

int main() {
    std::unordered_map<std::string, std::unique_ptr<Shape>> shapePrototypes;

    shapePrototypes["circle"] = std::make_unique<Circle>(10);
    shapePrototypes["rectangle"] = std::make_unique<Rectangle>(5, 8);

    auto clonedCircle = shapePrototypes["circle"]->clone();
    clonedCircle->draw();

    auto clonedRectangle = shapePrototypes["rectangle"]->clone();
    clonedRectangle->draw();

    return 0;
}
