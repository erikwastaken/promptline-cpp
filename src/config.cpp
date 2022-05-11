#include "config.hpp"
#include <filesystem>
#include <cstdlib>

Config::Config() {
    auto home = std::getenv("HOME");
    auto path = std::filesystem::path(home);
    path /= ".config/promptline-cpp/colors.toml";
    if (std::filesystem::exists(path)) {
        try {
            _config = ConfigParser(path.string()).config();
        } catch (ParserError &e) {}
    }
}

int Config::fg(const std::string &segmentName) const {
    return (_config.contains(segmentName)) ? _config.at(segmentName).first : _default.at(segmentName).first;
}

int Config::bg(const std::string &segmentName) const {
    return (_config.contains(segmentName)) ? _config.at(segmentName).second : _default.at(segmentName).second;
}
