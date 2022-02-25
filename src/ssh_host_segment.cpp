#include "ssh_host_segment.hpp"


SshHostSegment::SshHostSegment(int fg, int bg) : Segment(fg,bg) {
    if (std::getenv("SSH_CLIENT")) {
        _hostName += "\\H";
    }
}

std::string SshHostSegment::get() const {
    return _hostName;
}
