#include "config.hpp"
#include "toml.hpp"
#include <filesystem>
#include <cstdlib>

Config::Config() {
    auto home = std::getenv("HOME");
    auto config_path = std::filesystem::path(home) / ".config/promptline-cpp";
    // colors
    auto color_path = config_path / "colors.toml";
    if (std::filesystem::exists(color_path)) {
        auto colors = toml::parse_file(color_path.string());
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

    // segment order
    auto segment_path = config_path / "segments.toml";
    if (std::filesystem::exists(segment_path)) {
        auto segment_config = toml::parse_file(segment_path.string());
        for (auto header : segment_config) {
            std::vector<std::pair<std::string, int>> sorted_kv {};
            for (const auto& kv : header.second) {
                sorted_kv.emplace_back(kv.first, std::get<int>(kv.second));
            }
            std::stable_sort(std::begin(sorted_kv), std::end(sorted_kv), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second < b.second; });
            if (header.first == "left") {
                for (const auto& kv : sorted_kv) {
                    _segments_left.push_back(kv.first);
                }
            } else {
                for (const auto& kv : sorted_kv) {
                    _segments_right.push_back(kv.first);
                }
            }
        }
    } else {
        _segments_left = default_segments_left;
        _segments_right = default_segments_right;
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


std::vector<std::string> Config::left_segments() const {
    return _segments_left;
}

std::vector<std::string> Config::right_segments() const {
    return _segments_right;
}
