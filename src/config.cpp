#include "config.hpp"
#include <filesystem>
#include <cstdlib>

Config::Config() {
    auto home = std::getenv("HOME");
    auto path = std::filesystem::path(home);
    path /= ".config/powerline-cpp/colors.toml";
    if (std::filesystem::exists(path)) {
        try {
            _colors = ConfigParser(path.string()).colorConfig();
        } catch (ParserError &e) {}
    }
}

int Config::fg(const std::string &segmentName) const {
    return (_colors.contains(segmentName)) ? _colors.at(segmentName).first : _default.at(segmentName).first;
}

int Config::bg(const std::string &segmentName) const {
    return (_colors.contains(segmentName)) ? _colors.at(segmentName).second : _default.at(segmentName).second;
}
