#ifndef POWERLINEPP_CONFIG_PARSER_HPP
#define POWERLINEPP_CONFIG_PARSER_HPP

#include <string>
#include <exception>
#include <unordered_map>
#include <utility>
#include <fstream>

class ParserError : public std::exception { };

class ConfigParser {
    public:
        ConfigParser(const std::string &path = "colors.toml");
        ~ConfigParser();
        std::unordered_map<std::string, std::pair<int,int>> config();

    private:
        std::fstream _fs;
        std::unordered_map<std::string, std::pair<int,int>> _config;
};

#endif

