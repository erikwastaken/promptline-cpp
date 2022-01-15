#include "rc_segment.hpp"
#include "arrows.hpp"

RcSegment::RcSegment(int fg, int bg) : _fg(fg), _bg(bg) { }
    
std::string RcSegment::get() const {
    return "%?";
}
