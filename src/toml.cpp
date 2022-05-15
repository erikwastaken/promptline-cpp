#include "toml.hpp"
#include <fstream>
#include <cctype>
#include <iostream>
#include <exception>
#include <unordered_map>
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

toml::Lexer::Lexer(Reader *r) : _reader(r) {
    while (true) {
        auto tok = build_token();
        _tokens.push_back(tok);
        if (tok.kind() == Kind::EoF)
            break;
    }
}

toml::Token toml::Lexer::peak() const {
    if (i == _tokens.size())
        return _tokens.at(i -1);
    return _tokens.at(i);
}

toml::Token toml::Lexer::consume() {
    if (i == _tokens.size())
        return _tokens.at(i -1);
    return _tokens.at(i++);
}

toml::Token toml::Lexer::build_token() {
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
            while (std::isalnum(_reader->peak()) || _reader->peak() == '-') {
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

std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> toml::Parser::parse() {
    auto map = std::unordered_map<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>>();
    while (!is_done()) {
        auto sec = section();
        map[sec.first] = sec.second;
    }
    return map;
}

std::pair<std::string, std::unordered_map<std::string, std::variant<int, bool, std::string>>> toml::Parser::section() {
    auto h = header();
    auto map = std::unordered_map<std::string, std::variant<int, bool, std::string>>();
    auto tok = peak_token();
    while (tok.kind() != Kind::OpeningBrace && tok.kind() != Kind::EoF) {
        auto kva = key_value_assignment();
        map[kva.first] = kva.second;
        tok = peak_token();
    }
    return std::make_pair(h,map);
}

std::string toml::Parser::header() {
    auto tok = get_token();
    while (tok.kind() != Kind::OpeningBrace && !is_done()) {
        tok = get_token();
    }
    if (tok.kind() == Kind::OpeningBrace) {
        auto text = get_token();
        if (text.kind() != Kind::Text) {
            throw ParserError("header1");
        }
        if (get_token().kind() != Kind::ClosingBrace) {
            throw ParserError("header2");
        }
        return std::get<std::string>(text.value());
    } else {
        throw ParserError("header3");
    }
}

std::pair<std::string, std::variant<int, bool, std::string>> toml::Parser::key_value_assignment() {
    auto tok = get_token();
    while (tok.kind() == Kind::NewLine) {
        tok = get_token();
    }
    if (tok.kind() != Kind::Text) {
        throw ParserError("Expected Identifier");
    }
    auto tok2 = get_token();
    if (tok2.kind() != Kind::AssignmentOperator) {
        throw ParserError("Expected AssignmentOperator, got " + std::get<std::string>(tok2.value()));
    }
    auto val = value();
    auto key = std::get<std::string>(tok.value());
    return std::make_pair(key,val);
}

std::variant<int, bool, std::string> toml::Parser::value() {
    return get_token().value();
}

toml::Token toml::Parser::get_token() {
    auto tok = _lexer->consume();
    // ignore comments
    while (tok.kind() == Kind::Comment || tok.kind() == Kind::NewLine) {
        if (tok.kind() == Kind::EoF) {
            _eof = true;
            return tok;
        }
        tok = _lexer->consume();
    }
    return tok;
}

bool toml::Parser::is_done() const {
    return _eof;
}

toml::Token toml::Parser::peak_token() {
    // ignore comments
    while (_lexer->peak().kind() == Kind::Comment || _lexer->peak().kind() == Kind::NewLine) {
        _lexer->consume();
    }
    if (_lexer->peak().kind() == Kind::EoF) {
        _eof = true;
        return _lexer->peak();
    }
    return _lexer->peak();
}
