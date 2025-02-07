#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class TextConverter {
public:
    virtual void create_text() = 0;
    virtual void convert_character([[maybe_unused]] char c) {}
    virtual void convert_font([[maybe_unused]] const std::string font) {}
};

class AsciiText {
private:
    std::string text_;
public:
    AsciiText(const std::stringstream& stream) : text_(stream.str()) {}
    std::string text() const { return text_; }
};

class AsciiTextConverter : public TextConverter {
private:
    std::stringstream stream_;
public:
    virtual void create_text() override { stream_.clear(); }
    virtual void convert_character(char c) override { stream_ << c; }
    AsciiText get() const { return {stream_}; }
};

class TexText {
private:
    std::string text_;
public:
    TexText(const std::stringstream& stream) : text_(stream.str()) {}
    std::string text() const { return text_; }
};

class TexTextConverter : public TextConverter {
private:
    std::stringstream stream_;
public:
    virtual void create_text() override { stream_.clear(); }
    virtual void convert_character(char c) override {
        if (c == '\n') {
            stream_ << "\n\\newline\n";
        } else {
            stream_ << c;
        }
    }
    virtual void convert_font(const std::string font) override {
        stream_ << std::format("\\setfont({})\n", font);
    }
    TexText get() const { return {stream_}; }
};

class RtfDocument {
private:
    std::string text_;
    std::string font_;
public:
    RtfDocument(const std::string& text, const std::string& font)
            : text_(text), font_(font) {}
    std::string text() const { return text_; }
    std::string font() const { return font_; }
};

class RtfReader {
private:
    std::shared_ptr<TextConverter> text_converter_;
public:
    RtfReader(std::shared_ptr<TextConverter> text_converter)
            : text_converter_(text_converter) {}

    void set_builder(std::shared_ptr<TextConverter> text_converter) {
        text_converter_ = text_converter;
    }

    void parse_document(const RtfDocument& doc) {
        text_converter_->create_text();
        text_converter_->convert_font(doc.font());
        auto text = doc.text();
        for (char c : text) {
            text_converter_->convert_character(c);
        }
    }
};

[[gnu::weak]] int main() {
    RtfDocument rtf_doc("Hello, world!\nThis is just a text.\n",
                        "Liberation Serif");

    auto ascii_converter = std::make_shared<AsciiTextConverter>();
    auto rtf_reader = std::make_shared<RtfReader>(ascii_converter);
    rtf_reader->parse_document(rtf_doc);
    AsciiText ascii_text = ascii_converter->get();
    std::cout << "===================\n";
    std::cout << "This is ASCII text:\n" << ascii_text.text();

    auto tex_converter = std::make_shared<TexTextConverter>();
    rtf_reader->set_builder(tex_converter);
    rtf_reader->parse_document(rtf_doc);
    TexText tex_text = tex_converter->get();
    std::cout << "===================\n";
    std::cout << "This is Tex text:\n" << tex_text.text();

    return 0;
}
