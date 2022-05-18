#ifndef PROMPTLINE_TOML_HPP
#define PROMPTLINE_TOML_HPP

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <utility>

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

    class ParserError : public std::exception {
        public:
            explicit ParserError(std::string msg) : _msg(msg) {};
            virtual const char* what() const noexcept override { return _msg.c_str(); };
        private:
            std::string _msg {};
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
            signed short peak() const;
            signed short consume();
        private:
            unsigned long i {0};
            std::string _buffer {};
    };

    // turn output of Reader into token
    class Lexer {
        public:
            explicit Lexer(Reader *r);
            Token peak() const;
            Token consume();
        private:
            Reader *_reader;
            std::vector<Token> _tokens {};
            unsigned long i {0};
            Token build_token();
    };

    // turn tokens into result output
    class Parser {
        public:
            explicit Parser(Lexer *l);
            std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> parse();
        private:
            //std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> sections();
            std::pair<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> section();
            std::string header();
            std::pair<std::string, std::variant<int, bool, std::string>> key_value_assignment();
            std::variant<int, bool, std::string> value();
            Token get_token();
            Token peak_token();
            bool is_done() const;
            Lexer *_lexer;
            bool _eof {false};
    };

    std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> parse_file(const std::string &path);
}

#endif
