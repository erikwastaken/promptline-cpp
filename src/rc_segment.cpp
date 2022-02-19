#include "rc_segment.hpp"

RcSegment::RcSegment(int fg, int bg, int rc) : Segment(fg,bg), _rc(rc) { }
    
std::string RcSegment::get() const {
    return std::to_string(_rc);
}
