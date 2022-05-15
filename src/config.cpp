#include "config.hpp"
#include "toml.hpp"
#include <filesystem>
#include <cstdlib>

Config::Config() {
    auto home = std::getenv("HOME");
    auto path = std::filesystem::path(home);
    path /= ".config/promptline-cpp/colors.toml";
    if (std::filesystem::exists(path)) {
        auto colors = toml::parse_file(path.string());
        for (const auto &n : segment_names) {
            if (colors.contains(n)) {
                auto fg = _default.at(n).first;
                auto bg = _default.at(n).second;
                if (colors.at(n).contains("foreground")) {
                    fg = std::get<int>(colors.at(n).at("foreground"));
                }
                if (colors.at(n).contains("background")) {
                    bg = std::get<int>(colors.at(n).at("background"));
                }
                _colors[n] = std::make_pair(fg, bg);
            } else {
                _colors[n] = _default.at(n);
            }
        }
    } else {
        _colors = _default;
    }
}

int Config::fg(const std::string &segmentName) const {
    return _colors.at(segmentName).first;
    //return (_colors.contains(segmentName)) ? _colors.at(segmentName).first : _default.at(segmentName).first;
}

int Config::bg(const std::string &segmentName) const {
    return _colors.at(segmentName).second;
    //return (_colors.contains(segmentName)) ? _colors.at(segmentName).second : _default.at(segmentName).second;
}
