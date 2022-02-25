#include "ssh_host_segment.hpp"


SshHostSegment::SshHostSegment(int fg, int bg, Formatter* fmt) : Segment(fg,bg) {
    if (std::getenv("SSH_CLIENT")) {
        _hostName += fmt->hostname();
    }
}

std::string SshHostSegment::get() const {
    return _hostName;
}
