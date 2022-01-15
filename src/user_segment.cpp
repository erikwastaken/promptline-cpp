#include "user_segment.hpp"
#include <cstdlib>

UserSegment::UserSegment(int fg, int bg) : _fg(fg), _bg(bg) {
    if (auto user = std::getenv("USER"))
        _user = user;
    else _user = "%n";
}
    
std::string UserSegment::get() const {
    return _user;
    //auto result = arrow_start(_fg,_bg);
    //result += _user;
    //result += (_next == nullptr) ? last_arrow_end(_bg) : arrow_end(_bg, _next->bg());
    //return result;
}
