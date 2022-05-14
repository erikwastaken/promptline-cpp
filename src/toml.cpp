#include "toml.hpp"
#include <fstream>
#include <cctype>
#include <iostream>
#include <exception>
#include <variant>

toml::Token::Token(toml::Kind k, std::variant<int, bool, std::string> v) : _kind(k), _value(v) {}

toml::Reader::Reader(const std::string &path) {
    std::fstream ifs;
    ifs.open(path);
    if (!ifs.is_open()) {
        throw std::exception();
    } else {
        char c;
        while (ifs.get(c)) {
            _buffer += c;
        }
    }
}

char toml::Reader::peak() const {
    if (i == _buffer.length())
        return EOF;
    return _buffer.at(i);
}

char toml::Reader::consume() {
    if (i == _buffer.length())
        return EOF;
    return _buffer.at(i++);
}

toml::Lexer::Lexer(Reader *r) : _reader(r) { }

toml::Token toml::Lexer::consume() const {
    auto c = _reader->consume();
    while (std::isspace(c)) {
        c = _reader->consume();
    }
    switch (c) {
        case EOF:
            return Token{Kind::EoF, std::to_string(c)};
        case '"': {
            auto s = std::string();
            c = _reader->consume();
            while (c != '"') {
                s += c;
                c = _reader->consume();
            }
            return Token{Kind::Value, s};
        }
        case '[': {
            auto s = std::string();
            c = _reader->consume();
            while (c != ']') {
                s += c;
                c = _reader->consume();
            }
            return Token{Kind::Header, s};
        }
        case '#': {
            auto s = std::string();
            while (_reader->peak() != '\n') {
                c = _reader->consume();
                s += c;
            }
            return Token{Kind::Comment, s};
        }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            auto s = std::string();
            while (std::isdigit(c)) {
                s += c;
                c = _reader->consume();
            }
            return Token{Kind::Value, std::stoi(s)};
        }
        case '=': return Token{Kind::AssignmentOperator, std::to_string(c)};
        default: {
            auto s = std::string();
            while (_reader->peak() != '=') {
                if (!isspace(c))
                    s += c;
                c = _reader->consume();
            }
            return Token{Kind::Key, s};
        }
    }
}

void toml::debug() {
    auto r = Reader("test.toml");
    auto lex = Lexer(&r);
    auto tok = lex.consume();
    while (tok.kind() != Kind::EoF) {
        std::visit([](auto&& arg){std::cout << arg << '\n';}, tok.value());
        tok = lex.consume();
    }
}
