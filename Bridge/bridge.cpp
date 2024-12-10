#include <iostream>
#include <memory>
#include <string>

class Color {
public:
    virtual std::string applyColor() const = 0;
    virtual ~Color() = default;
};

class Red : public Color {
public:
    std::string applyColor() const override {
        return "Red";
    }
};
class Blue : public Color {
public:
    std::string applyColor() const override {
        return "Blue";
    }
};
class Shape {
protected:
    std::shared_ptr<Color> color;
public:
    Shape(std::shared_ptr<Color> col) : color(std::move(col)) {}
    virtual void draw() const = 0; 
    virtual ~Shape() = default;
};
class Circle : public Shape {
private:
    float radius;
public:
    Circle(float r, std::shared_ptr<Color> col) : Shape(std::move(col)), radius(r) {}

    void draw() const override {
        std::cout << "Drawing a Circle of radius " << radius << " with " 
                  << color->applyColor() << " color.\n";
    }
};
class Rectangle : public Shape {
private:
    float width, height;
public:
    Rectangle(float w, float h, std::shared_ptr<Color> col)
        : Shape(std::move(col)), width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing a Rectangle of width " << width 
                  << " and height " << height << " with " 
                  << color->applyColor() << " color.\n";
    }
};

int main() {
    std::shared_ptr<Color> red = std::make_shared<Red>();
    std::shared_ptr<Color> blue = std::make_shared<Blue>();
    Circle redCircle(5, red);
    Rectangle blueRectangle(4, 6, blue);
    redCircle.draw();
    blueRectangle.draw();

    return 0;
}
