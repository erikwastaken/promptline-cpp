#ifndef PROMPTLINE_CONFIG_HPP
#define PROMPTLINE_CONFIG_HPP

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
            {"user", {15,4}},
            {"cwd", {15,8}},
            {"git", {15,0}},
            {"exit-code", {15,1}},
            {"virtual-environment", {15,5}},
            {"ssh", {15,9}},
            {"time", {15,4}}
        };
        std::unordered_map<std::string, std::pair<int, int>> _config {};
};

#endif

