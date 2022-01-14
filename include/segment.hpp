#include <string>
#include <iostream>

class Segment {
    public:
        auto static constexpr right_triangle = "\ue0b0";
        auto static arrow_start(int fg, int bg) {
            return "%F{" + std::to_string(fg) + "}%K{" + std::to_string(bg) + "}%B ";
        }
        auto static arrow_end(int fg, int bg) {
            return " %b%F{reset}%K{reset}%{%F{" + std::to_string(fg) + "}%}%{%K{" + std::to_string(bg) + "}%}" + right_triangle + "%F{reset}%K{reset}"; 
        }
        auto static last_arrow_end(int fg) {
            return " %b%F{reset}%K{reset}%{%F{" + std::to_string(fg) + "}%}" + right_triangle + "%F{reset}%K{reset}"; 
        }
        Segment(const std::string &content, int fg, int bg, Segment* next = nullptr);
        std::string get() const;
        int fg() const { return _fg; };
        int bg() const { return _bg; };
        void next(Segment *n) { _next = n; };
    private:
        std::string _content;
        int _fg;
        int _bg;
        Segment *_next;
};

std::ostream& operator<<(std::ostream& out, const Segment &s);
