#ifndef PROMPTLINE_CONFIG_HPP
#define PROMPTLINE_CONFIG_HPP

#include <string>
#include <exception>
#include <unordered_map>
#include <utility>
#include <array>
#include <vector>

class Config {
    public:
        Config();
        int fg(const std::string &segmentName) const;
        int bg(const std::string &segmentName) const;
        std::vector<std::string> left_segments() const;
        std::vector<std::string> right_segments() const;
    private:
        const inline static std::unordered_map<std::string, std::pair<int,int>> _default {
            {"user", {15,4}},
            {"cwd", {15,8}},
            {"git", {15,0}},
            {"exit-code", {15,1}},
            {"virtual-environment", {15,5}},
            {"ssh", {15,9}},
            {"time", {15,4}}
        };
        const inline static std::array<std::string, 7> segment_names {
                "user",
                "cwd",
                "git",
                "exit-code",
                "virtual-environment",
                "ssh",
                "time"
        };
        const inline static std::vector<std::string> default_segments_left {"exit-code", "ssh", "user", "virtual-environment", "git", "cwd"};
        const inline static std::vector<std::string> default_segments_right {"time"};

        std::unordered_map<std::string, std::pair<int, int>> _colors {};
        std::vector<std::string> _segments_left {};
        std::vector<std::string> _segments_right {};
};

#endif

