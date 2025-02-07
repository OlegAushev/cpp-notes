#include <memory>
#include <print>

class ShapePrototype {
public:
    virtual std::shared_ptr<ShapePrototype> clone() const = 0;
    virtual void move(double x, double y) = 0;
    virtual void draw() const = 0;
};

class GraphicTool {
private:
public:
    std::shared_ptr<ShapePrototype>
    manipulate(const ShapePrototype& prototype) {
        auto p = prototype.clone();
        p->move(1.0, 2.0);
        return p;
    }
};

struct Point {
    double x;
    double y;
};

void move(Point& p, double x, double y) {
    p.x += x;
    p.y += y;
}

class Circle : public ShapePrototype {
private:
    Point center_;
    double radius_;
public:
    Circle(const Point& center, double radius)
            : center_(center), radius_(radius) {}

    virtual std::shared_ptr<ShapePrototype> clone() const override {
        return std::make_shared<Circle>(*this);
    }

    virtual void move(double x, double y) override { ::move(center_, x, y); }

    virtual void draw() const override {
        std::print(
                "Circle: c={{{},{}}}, r={}\n", center_.x, center_.y, radius_);
    }
};

class Triangle : public ShapePrototype {
private:
    Point a_;
    Point b_;
    Point c_;
public:
    Triangle(const Point& a, const Point& b, const Point& c)
            : a_(a), b_(b), c_(c) {}

    virtual std::shared_ptr<ShapePrototype> clone() const override {
        return std::make_shared<Triangle>(*this);
    }

    virtual void move(double x, double y) override {
        ::move(a_, x, y);
        ::move(b_, x, y);
        ::move(c_, x, y);
    }

    virtual void draw() const override {
        std::print("Triangle: a={{{},{}}}, b={{{},{}}}, c={{{},{}}}\n",
                   a_.x,
                   a_.y,
                   b_.x,
                   b_.y,
                   c_.x,
                   c_.y);
    }
};

class Rectangle : public ShapePrototype {
private:
    Point topleft_;
    double width_;
    double height_;
public:
    Rectangle(const Point& topleft, double width, double height)
            : topleft_(topleft), width_(width), height_(height) {}

    virtual std::shared_ptr<ShapePrototype> clone() const override {
        return std::make_shared<Rectangle>(*this);
    }

    virtual void move(double x, double y) override { ::move(topleft_, x, y); }

    virtual void draw() const override {
        std::print("Rectangle: topleft={{{},{}}}, w={}, h={}\n",
                   topleft_.x,
                   topleft_.y,
                   width_,
                   height_);
    }
};

[[gnu::weak]] int main() {
    Circle circle({0, 0}, 1);
    Triangle triangle({1, 1}, {2, 2}, {3, 0});
    Rectangle rectangle({-5, 0}, 3, 2);

    GraphicTool graphic_tool;

    auto manipulated_shape1 = graphic_tool.manipulate(circle);
    auto manipulated_shape2 = graphic_tool.manipulate(triangle);
    auto manipulated_shape3 = graphic_tool.manipulate(rectangle);

    std::print("Original shapes:\n");
    circle.draw();
    triangle.draw();
    rectangle.draw();

    std::print("Manipulated shapes:\n");
    manipulated_shape1->draw();
    manipulated_shape2->draw();
    manipulated_shape3->draw();

    return 0;
}
