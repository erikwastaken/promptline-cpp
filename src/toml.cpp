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
    while (c != '\n' && std::isspace(c)) {
        c = _reader->consume();
    }
    switch (c) {
        case EOF:
            return Token{Kind::EoF, "EOF"};
        case '\n':
            return Token{Kind::NewLine, "NewLine"};
        case '[':
            return Token{Kind::OpeningBrace, "["};
        case ']':
            return Token{Kind::ClosingBrace, "]"};
        case '"': {
            auto s = std::string();
            c = _reader->consume();
            while (c != '"') {
                s += c;
                c = _reader->consume();
            }
            return Token{Kind::String, s};
        }
        case '#': {
            auto s = std::string("Comment: ");
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
            while (std::isdigit(_reader->peak())) {
                s += c;
                c = _reader->consume();
            }
            s += c;
            return Token{Kind::Number, std::stoi(s)};
        }
        case '=': return Token{Kind::AssignmentOperator, "="};
        default: {
            auto s = std::string();
            while (std::isalnum(_reader->peak())) {
                if (!isspace(c))
                    s += c;
                c = _reader->consume();
            }
            s += c; // take the last alphanumerical char
            return Token{Kind::Text, s};
        }
    }
}

toml::Parser::Parser(toml::Lexer *l) : _lexer(l) {};

std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> toml::Parser::parse() const {
    auto map = std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>>();
    auto tok = _lexer->consume();
    while (tok.kind() != Kind::EoF) {
    //    if (tok.kind() == Kind::Header) {
    //        std::string header = std::get<std::string>(tok.value());
    //        while (tok.kind() != Kind::Header && tok.kind() != Kind::EoF) {
    //            tok = _lexer->consume();
    //            auto key = std::string();
    //            switch (tok.kind()) {
    //                case Kind::Key:
    //                    key = std::get<std::string>(tok.value());
    //                    break;
    //                case Kind::Value:
    //                    if (key.length() != 0) {
    //                        map[header][key] = tok.value();
    //                        key = "";
    //                    } else {
    //                        throw std::exception();
    //                    }
    //                    break;
    //                default:
    //                    break; //ignore the rest
    //            }
    //        }
    //    } else {
    //        tok = _lexer->consume();
    //    }
    }
    return map;
}

void toml::debug() {
    auto r = Reader("test.toml");
    auto lex = Lexer(&r);
    auto tok = lex.consume();
    while (tok.kind() != Kind::EoF) {
        std::visit([](auto&& arg){std::cout << arg << '\n';}, tok.value());
        tok = lex.consume();
    }
    std::visit([](auto&& arg){std::cout << arg << '\n';}, tok.value());
    //auto p = Parser(&lex);
    //auto map = p.parse();
    //for (auto k : map) {
    //    for (auto kk : k.second) {
    //        std::visit([](auto&& arg){std::cout << arg << '\n';}, kk.second);
    //    }
    //}
}
