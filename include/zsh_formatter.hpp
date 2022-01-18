#ifndef POWERLINEPP_ZSH_FORMATTER_HPP
#define POWERLINEPP_ZSH_FORMATTER_HPP

#include "formatter.hpp"

class ZshFormatter : public Formatter {
    public:
        ZshFormatter() = default;
        virtual std::string boldOn() const override { return "\033[1m"; };
        virtual std::string fgColor(int color) const override { return "\033[38;5;" + std::to_string(color) + "m"; };
        virtual std::string bgColor(int color) const override { return "\033[48;5;" + std::to_string(color) + "m"; };
        virtual std::string reset() const override { return "\033[0m"; };

        virtual std::string arrow_start(int fg, int bg) const override {
            return fgColor(fg) + bgColor(bg) + boldOn() + " ";
        }
        virtual std::string arrow_end(int fg, int bg) const override {
            return " " + reset() + fgColor(fg) + bgColor(bg) + right_triangle + reset();
        }
        virtual std::string last_arrow_end(int fg) const override {
            return " " + reset() + fgColor(fg) + right_triangle + reset();
        }
};

#endif

