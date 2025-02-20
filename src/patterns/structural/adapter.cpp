#include <compare>
#include <memory>
#include <print>
#include <utility>

struct Point {
    int x;
    int y;
};

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual std::pair<Point, Point> bounding_box() const = 0;
    // ...
};

class TextView {
private:
    Point origin_;
    int width_;
    int height_;
public:
    TextView(Point origin, int width, int height)
            : origin_(origin), width_(width), height_(height) {}
    virtual ~TextView() = default;
    Point origin() const { return origin_; }
    int width() const { return width_; }
    int height() const { return height_; }
};

// (1)
class TextShape1 : public Shape, private TextView {
public:
    TextShape1(Point origin, int width, int height)
            : TextView(origin, width, height) {}

    virtual std::pair<Point, Point> bounding_box() const override {
        Point bottomleft = origin();
        Point topleft{bottomleft.x, bottomleft.y + height()};
        Point bottomright{bottomleft.x + width(), bottomleft.y};
        return {topleft, bottomright};
    }
};

// (2)
class TextShape2 : public Shape {
private:
    TextView& textview_;
public:
    TextShape2(TextView& textview) : textview_(textview) {}

    virtual std::pair<Point, Point> bounding_box() const override {
        Point bottomleft = textview_.origin();
        Point topleft{bottomleft.x, bottomleft.y + textview_.height()};
        Point bottomright{bottomleft.x + textview_.width(), bottomleft.y};
        return {topleft, bottomright};
    }
};

[[gnu::weak]] int main() {
    std::unique_ptr<Shape> shape1 =
            std::make_unique<TextShape1>(Point{1, 1}, 10, 2);
    auto box1 = shape1->bounding_box();
    std::println("Box: ({},{}),({},{})",
                 box1.first.x,
                 box1.first.y,
                 box1.second.x,
                 box1.second.y);

    TextView text(Point{10, 20}, 20, 2);
    std::unique_ptr<Shape> shape2 = std::make_unique<TextShape2>(text);
    auto box2 = shape2->bounding_box();
    std::println("Box: ({},{}),({},{})",
                 box2.first.x,
                 box2.first.y,
                 box2.second.x,
                 box2.second.y);

    return 0;
}
