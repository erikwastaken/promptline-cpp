#include "config_parser.hpp"

ConfigParser::ConfigParser(const std::string &path) {
    _fs.open(path);
    if (!_fs.is_open())
        throw ParserError();
}

ConfigParser::~ConfigParser() {
    _fs.close();
}

const std::unordered_map<std::string, std::pair<int,int>> ConfigParser::config() {
    std::unordered_map<std::string, std::pair<int,int>> config;
    auto key = std::string();
    auto foreground = 0;
    auto background = 0;
    for (std::string line; std::getline(_fs, line); ) {
        if (line.starts_with('[')) {
            key = line.substr(1,line.length() - 2);
        } else if (line.starts_with("foreground")) {
            foreground = std::stoi(line.substr(11));
        } else if (line.starts_with("background")) {
            background = std::stoi(line.substr(11));
        } else {
            config[key] = std::make_pair(foreground, background);
        }
    }
    config[key] = std::make_pair(foreground, background);
    return config;
}
