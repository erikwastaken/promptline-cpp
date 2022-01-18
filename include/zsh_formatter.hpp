#ifndef POWERLINEPP_ZSH_FORMATTER_HPP
#define POWERLINEPP_ZSH_FORMATTER_HPP

#include "formatter.hpp"

class ZshFormatter : public Formatter {
    public:
        ZshFormatter() = default;
        virtual std::string boldOn() const override { return "%B"; };
        virtual std::string fgColor(int color) const override { return "%F{" + std::to_string(color) + "}"; };
        virtual std::string bgColor(int color) const override { return "%K{" + std::to_string(color) + "}"; };
        virtual std::string reset() const override { return resetFg() + resetBg() + boldOff(); };

        virtual std::string arrow_start(int fg, int bg) const override {
            return fgColor(fg) + bgColor(bg) + boldOn() + " ";
        }
        virtual std::string arrow_end(int fg, int bg) const override {
            return " " + boldOff() + resetFg() + resetBg() + "%{" + fgColor(fg) + "%}" + "%{" + bgColor(bg) + "%}" + right_triangle + resetFg() + resetBg();
        }
        virtual std::string last_arrow_end(int fg) const override {
            return " " + boldOff() + resetFg() + resetBg() + "%{" + fgColor(fg) + "%}" + right_triangle + resetFg() + resetBg();
        }
    private:
        std::string resetFg() const { return "%F{reset}"; };
        std::string resetBg() const { return "%K{reset}"; };
        std::string boldOff() const { return "%b"; };
};

#endif

