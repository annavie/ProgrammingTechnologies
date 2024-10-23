#include <iostream>
#include <vector>
#include <memory>

class Component {
public:
    virtual ~Component() {}
    virtual void operation() const = 0;
};

class Leaf : public Component {
public:
    void operation() const override {
        std::cout << "Leaf\n";
    }
};

class Composite : public Component {
public:
    void add(std::unique_ptr<Component> component) {
        children_.emplace_back(std::move(component));
    }

    void operation() const override {
        std::cout << "Composite containing:\n";
        for (const auto& child : children_) {
            child->operation();
        }
    }

private:
    std::vector<std::unique_ptr<Component>> children_;
};

int main() {
    auto composite = std::make_unique<Composite>();
    composite->add(std::make_unique<Leaf>());
    composite->add(std::make_unique<Leaf>());

    auto subComposite = std::make_unique<Composite>();
    subComposite->add(std::make_unique<Leaf>());
    composite->add(std::move(subComposite));

    composite->operation();

    return 0;
}
