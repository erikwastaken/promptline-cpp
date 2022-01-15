#ifndef POWERLINEPP_ARROWS_HPP
#define POWERLINEPP_ARROWS_HPP

#include <string>

namespace arrows {

    auto static constexpr right_triangle = "\ue0b0";
    auto static constexpr right_angle = "\ue0b1";
    auto static constexpr left_triangle = "\ue0b2";
    auto static constexpr left_angle = "\ue0b3";

    auto static arrow_start(int fg, int bg) {
        return "%F{" + std::to_string(fg) + "}%K{" + std::to_string(bg) + "}%B ";
    }
    auto static arrow_end(int fg, int bg) {
        return " %b%F{reset}%K{reset}%{%F{" + std::to_string(fg) + "}%}%{%K{" + std::to_string(bg) + "}%}" + right_triangle + "%F{reset}%K{reset}"; 
    }
    auto static last_arrow_end(int fg) {
        return " %b%F{reset}%K{reset}%{%F{" + std::to_string(fg) + "}%}" + right_triangle + "%F{reset}%K{reset}"; 
    }

}

#endif
