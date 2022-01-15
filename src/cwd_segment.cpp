#include "cwd_segment.hpp"
#include "arrows.hpp"
#include <filesystem>
#include <cstdlib>

CwdSegment::CwdSegment(int fg, int bg) : _fg(fg), _bg(bg) {
    auto path = std::filesystem::current_path();
    auto home = std::filesystem::path(std::getenv("HOME"));
    if (path == home) {
        _cwd = "~";
       return;
    }
    if (path == path.root_path()) {
        _cwd = path;
        return;
    }
    auto it = path.begin();
    auto containsHome = false;
    for (auto p = std::filesystem::path(); const auto &dir : path) {
        p /= dir;
        ++it;
        if (p == home) {
            containsHome = true;
            break;
        }
    }
    // bold off and dimmed color for parent directories
    _cwd = "%b%F{" + std::to_string(_fg - 4) + "}";
    if (containsHome) {
        _cwd += "~";
        for (auto i = it; i != --path.end(); ++i) {
            _cwd += " ";
            _cwd += arrows::right_angle;
            _cwd += " ";
            _cwd += *i;
        }
    } else {
        _cwd += *path.begin();
        for (const auto &dir : path) {
            if (dir == *path.begin() || dir == *(--path.end()))
                continue;
            _cwd += " ";
            _cwd += arrows::right_angle;
            _cwd += " ";
            _cwd += dir;
        }
    }
    _cwd += " ";
    _cwd += arrows::right_angle;
    _cwd += " ";
    // switch back Bold font and foreground color
    _cwd += "%B%F{" + std::to_string(_fg) + "}";
    _cwd += *(--path.end());
}
    
std::string CwdSegment::get() const {
    return _cwd;
}
