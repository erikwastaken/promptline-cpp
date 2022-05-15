#include "toml.hpp"
#include <iostream>

int main() {
    //auto r = toml::Reader("test.toml");
    auto r = toml::Reader("powerline-gruvbox.toml");
    auto lex = toml::Lexer(&r);
    //auto tok = lex.consume();
    //while (tok.kind() != toml::Kind::EoF) {
    //    std::visit([](auto&& arg){std::cout << arg << '\n';}, tok.value());
    //    tok = lex.consume();
    //}
    //std::visit([](auto&& arg){std::cout << arg << '\n';}, tok.value());
    auto p = toml::Parser(&lex);
    auto map = p.parse();
    for (auto k : map) {
        for (auto kk : k.second) {
            std::cout << kk.first << '\t';
            std::visit([](auto&& arg){std::cout << arg << '\n';}, kk.second);
        }
    }
}
