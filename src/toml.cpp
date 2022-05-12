#include "toml.hpp"
#include <fstream>

toml::Token::Token(toml::Kind k, std::variant<int, bool, std::string> v) : _kind(k), _value(v) {}

toml::Reader::Reader(const std::string &path) {
    if (std::fstream ifs; !ifs.is_open()) {
        //TODO handle errors
    } else {
        char c;
        while (ifs.get(c)) {
            _buffer += c;
        }
    }
}

char toml::Reader::peak() const {
    return _buffer.at(i);
}

char toml::Reader::peak(int k) const {
    //TODO handle out-of-range
    return _buffer.at(i+k);
}

char toml::Reader::consume() {
    return _buffer.at(i++);
}

toml::Lexer::Lexer(Reader *r) {
    //TODO tokenize reader content
    
}

const toml::Token& toml::Lexer::peak() const {
    return _tokens.at(i);
}

const toml::Token& toml::Lexer::peak(int k) const {
    //TODO handle out-of-range
    return _tokens.at(i+k);
}

const toml::Token& toml::Lexer::consume() {
    return _tokens.at(i++);
}
