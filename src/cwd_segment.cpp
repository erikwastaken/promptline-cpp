#include "cwd_segment.hpp"
#include <filesystem>
#include <cstdlib>

CwdSegment::CwdSegment(int fg, int bg, const Formatter* fmt) : Segment(fg,bg) {
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
    _cwd = fmt->reset() + fmt->fgColor(Segment::fg()) + fmt->bgColor(Segment::bg());
    if (containsHome) {
        _cwd += "~";
        for (auto i = it; i != --path.end(); ++i) {
            _cwd += " ";
            _cwd += fmt->right_angle;
            _cwd += " ";
            _cwd += *i;
        }
    } else {
        _cwd += *path.begin();
        for (const auto &dir : path) {
            if (dir == *path.begin() || dir == *(--path.end()))
                continue;
            _cwd += " ";
            _cwd += fmt->right_angle;
            _cwd += " ";
            _cwd += dir;
        }
    }
    _cwd += " ";
    _cwd += fmt->right_angle;
    _cwd += " ";
    _cwd += fmt->boldOn() + fmt->fgColor(Segment::fg()) + fmt->bgColor(Segment::bg());
    _cwd += *(--path.end());
}
    
std::string CwdSegment::get() const {
    return _cwd;
}
