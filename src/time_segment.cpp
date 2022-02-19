#include "time_segment.hpp"

TimeSegment::TimeSegment(int fg, int bg) : Segment(fg,bg) { }
    
std::string TimeSegment::get() const {
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string ts = std::ctime(&t);
    ts.resize(ts.size() - 1);
    return ts;
}
