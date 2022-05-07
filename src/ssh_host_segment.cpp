#include "ssh_host_segment.hpp"

SshHostSegment::SshHostSegment(int fg, int bg, Formatter* fmt) : Segment(fg,bg) {
    if (std::getenv("SSH_CLIENT")) {
        // reset bold to properly display padlock glyph
        _hostName += fmt->reset();
        _hostName += fmt->fgColor(fg);
        _hostName += fmt->bgColor(bg);
        _hostName += "\ue0a2 ";
        _hostName += fmt->boldOn();
        _hostName += fmt->hostname();
    }
}

std::string SshHostSegment::get() const {
    return _hostName;
}
