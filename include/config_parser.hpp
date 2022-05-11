#ifndef PROMPTLINE_CONFIG_PARSER_HPP
#define PROMPTLINE_CONFIG_PARSER_HPP

#include <string>
#include <exception>
#include <unordered_map>
#include <utility>
#include <fstream>

class ParserError : public std::exception { };

class ConfigParser {
    public:
        ConfigParser(const std::string &path);
        ~ConfigParser();
        const std::unordered_map<std::string, std::pair<int,int>> colorConfig();

    private:
        std::fstream _fs;
};

#endif

