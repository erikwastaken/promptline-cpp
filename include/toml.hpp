#ifndef PROMPTLINE_TOML_HPP
#define PROMPTLINE_TOML_HPP

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

namespace toml {

    enum class Kind {
        Comment,
        AssignmentOperator,
        OpeningBrace,
        ClosingBrace,
        NewLine,
        Text,
        Number,
        String,
        EoF
    };

    class Token {
        public:
            Token(Kind, std::variant<int, bool, std::string>);
            Kind kind() const { return _kind; };
            auto value() const { return _value; };
        private:
            Kind _kind;
            std::variant<int, bool, std::string> _value;
    };

    // interface to read a toml source char by char
    class Reader {
        public:
            explicit Reader(const std::string &path);
            char peak() const;
            char consume();
        private:
            unsigned long i {0};
            std::string _buffer {};
    };

    // turn output of Reader into token
    class Lexer {
        public:
            explicit Lexer(Reader *r);
            Token consume() const;
        private:
            enum class State {
                Normal,
                String,
                Comment,
                Header
            };
            Reader *_reader;
    };

    // turn tokens into result output
    class Parser {
        public:
            explicit Parser(Lexer *l);
            std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> parse() const;
        private:
            Lexer *_lexer;
    };

    void debug();
}

#endif
