#include "segment.hpp"

Segment::Segment(const std::string &content, int fg, int bg, Segment* next) : _content(content), _fg(fg), _bg(bg), _next(next) { }

std::string Segment::get() const {
    auto result = Segment::arrow_start(_fg,_bg);
    result += _content;
    result += (_next == nullptr) ? Segment::last_arrow_end(_bg) : Segment::arrow_end(_bg, _next->bg());
    return result;
}

std::ostream& operator<<(std::ostream& out, const Segment &s) {
    out << s.get();
    return out;
}
