#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Manipulator {
public:
    virtual void drag() = 0;
    virtual ~Manipulator() = default;
};

class LineFigure;
class LineManipulator : public Manipulator {
private:
    LineFigure& line_;
public:
    LineManipulator(LineFigure& line) : line_(line) {}

    virtual void drag();
};

class TextFigure;
class TextManipulator : public Manipulator {
private:
    TextFigure& text_;
public:
    TextManipulator(TextFigure& text) : text_(text) {}

    virtual void drag();
};

class Figure {
public:
    virtual ~Figure() = default;
    virtual std::unique_ptr<Manipulator> create_manipulator() = 0;
};

class LineFigure : public Figure {
private:
    std::pair<int, int> begin_{0, 0};
    std::pair<int, int> end_{0, 0};
public:
    LineFigure(std::pair<int, int> begin, std::pair<int, int> end)
            : begin_(begin), end_(end) {}

    virtual std::unique_ptr<Manipulator> create_manipulator() {
        return std::make_unique<LineManipulator>(*this);
    }

    auto begin() const { return begin_; }
    auto end() const { return end_; }
};

class TextFigure : public Figure {
private:
    std::string text_;
public:
    TextFigure(const std::string& text) : text_(text) {}

    virtual std::unique_ptr<Manipulator> create_manipulator() {
        return std::make_unique<TextManipulator>(*this);
    }

    std::string text() const { return text_; }
};

void LineManipulator::drag() {
    std::cout << "Dragging line {" << line_.begin().first << ","
              << line_.begin().second << "}-{" << line_.end().first << ","
              << line_.end().second << "}...\n";
}

void TextManipulator::drag() {
    std::cout << "Dragging text: <" << text_.text() << ">...\n";
}

int main() {
    std::vector<std::shared_ptr<Figure>> figures;

    auto line = std::make_shared<LineFigure>(std::make_pair(-1, -2),
                                             std::make_pair(3, 4));
    figures.push_back(line);
    auto text = std::make_shared<TextFigure>("some text");
    figures.push_back(text);

    for (auto& figure : figures) {
        auto manipulator = figure->create_manipulator();
        manipulator->drag();
    }

    return 0;
}
