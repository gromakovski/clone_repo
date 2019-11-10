// Factory

#include <boost/function.hpp>
#include <boost/functional/factory.hpp>

#include <map>
#include <string>
#include <iostream>

struct Shape {
    virtual ~Shape() {};

    virtual void draw() = 0;
};

struct Circle : Shape {
    void draw() override {
        std::cout << "circle" << std::endl;
    }
};

struct Box : Shape {
    void draw() override {
        std::cout << "box" << std::endl;
    }
};


int main() {
    std::map<std::string, boost::function<Shape *()>> factories;

    factories["circle"] = boost::factory<Circle *>();
    factories["box"] = boost::factory<Box *>();

    auto r = factories["box"]();

    r->draw();

    delete r;
}
