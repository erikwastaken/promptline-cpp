#include "config.hpp"

Config::Config() { }

Config::Config(const std::string &path) {
    try {
        _config = ConfigParser(path).config();
    } catch (ParserError &e) {
        Config();
    }
}

int Config::fg(const std::string &segmentName) const {
    return (_config.contains(segmentName)) ? _config.at(segmentName).first : _default.at(segmentName).first;
}

int Config::bg(const std::string &segmentName) const {
    return (_config.contains(segmentName)) ? _config.at(segmentName).second : _default.at(segmentName).second;
}
