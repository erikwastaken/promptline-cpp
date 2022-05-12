#ifndef PROMPTLINE_TOML_HPP
#define PROMPTLINE_TOML_HPP

#include <string>
#include <variant>
#include <vector>

namespace toml {

    enum class Kind {
        Header,
        Key,
        AssignmentOperator,
        Value
    };

    class Token {
        public:
            Token(Kind, std::variant<int, bool, std::string>);
            const Kind kind() const { return _kind; };
            const auto value() const { return _value; };
        private:
            Kind _kind;
            std::variant<int, bool, std::string> _value;
    };

    // interface to read a toml source char by char
    class Reader {
        public:
            explicit Reader(const std::string &path);
            char peak() const;
            char peak(int) const;
            char consume();
        private:
            int i {0};
            std::string _buffer {};
    };

    // turn output of Reader into token
    class Lexer {
        public:
            explicit Lexer(Reader *r);
            const Token& peak() const;
            const Token& peak(int) const;
            const Token& consume();
        private:
            int i {0};
            std::vector<Token> _tokens;
    };

}

#endif

