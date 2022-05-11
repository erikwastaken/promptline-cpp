#ifndef PROMPTLINE_FORMATTER_HPP
#define PROMPTLINE_FORMATTER_HPP

#include <string>

class Formatter {
    public:
        virtual ~Formatter() = default;
        auto static constexpr right_triangle = "\ue0b0";
        auto static constexpr right_angle = "\ue0b1";
        auto static constexpr left_triangle = "\ue0b2";
        auto static constexpr left_angle = "\ue0b3";

        virtual std::string boldOn() const = 0;
        virtual std::string fgColor(int color) const = 0;
        virtual std::string bgColor(int color) const = 0;
        virtual std::string reset() const = 0;

        virtual std::string arrow_start(int fg, int bg) const = 0;
        virtual std::string arrow_end(int fg, int bg) const = 0;
        virtual std::string last_arrow_end(int fg) const = 0;
        virtual std::string right_arrow_start(int fg, int bg) const = 0;
        virtual std::string right_arrow_end() const = 0;
        virtual std::string right_last_arrow_end() const = 0;

        virtual std::string hostname() const = 0;
};

#endif

