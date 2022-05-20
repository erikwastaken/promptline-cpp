#include "test_case.hpp"
#include "toml.hpp"

int lexerExistsProperlyWhenPeakingEmpty() {
    // Given a Lexer with an "empty" reader
    auto r = toml::Reader(std::string(""));
    auto cut = toml::Lexer(&r);
    // When consuming or peaking
    auto result = cut.consume();
    // Then returns End of File token
    auto rc = test::TestCase(
            "Lexer exits properly when consuming EoF"
            ).assert_equals(toml::Kind::EoF, result.kind());
    rc += test::TestCase(
            "Lexer exits properly when peaking EoF"
            ).assert_equals(toml::Kind::EoF, cut.peak().kind());
    return rc;
}

int parsesCorrectly() {
    // Given a Parser
    auto r = toml::Reader(std::string("[header]\nkey1 = 1\n"));
    auto l = toml::Lexer(&r);
    auto p = toml::Parser(&l);
    // When parsing
    auto result = p.parse();
    auto value = std::get<int>(result.at("header").at("key1"));
    // Then returns the correct value
    int rc = 0;
    rc += test::TestCase("Parses correctly").assert_equals(1, value);
    return rc;
}

int parsesEmptyReader() {
    // Given a Parser for an empty Reader
    auto r = toml::Reader(std::string(""));
    auto l = toml::Lexer(&r);
    auto p = toml::Parser(&l);
    // When parsing
    auto result = p.parse();
    // Then returns the correct value
    int rc = 0;
    rc += test::TestCase("Parses empty Reader").assert_equals(true, result.empty());
    return rc;
}

int main() {
    int rc = 0;
    rc += lexerExistsProperlyWhenPeakingEmpty();
    rc += parsesCorrectly();
    rc += parsesEmptyReader();
    return rc;
}
