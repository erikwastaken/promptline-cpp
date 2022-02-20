#ifndef POWERLINEPP_CONFIG_HPP
#define POWERLINEPP_CONFIG_HPP

#include "config_parser.hpp"
#include <string>
#include <exception>
#include <unordered_map>
#include <utility>

class Config {
    public:
        Config();
        int fg(const std::string &segmentName) const;
        int bg(const std::string &segmentName) const;
    private:
        const inline static std::unordered_map<std::string, std::pair<int,int>> _default {
            {"user", {255,31}},
            {"cwd", {255,241}},
            {"git", {255,238}},
            {"exit-code", {255,88}},
            {"virtual-environment", {255,38}},
            {"ssh", {255,208}},
            {"time", {255,31}}
        };
        std::unordered_map<std::string, std::pair<int, int>> _config {};
};

#endif

