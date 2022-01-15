#include "segment.hpp"

std::ostream& operator<<(std::ostream& out, const Segment &s) {
    out << s.get();
    return out;
}
