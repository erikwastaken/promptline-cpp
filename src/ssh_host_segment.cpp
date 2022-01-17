#include "ssh_host_segment.hpp"


SshHostSegment::SshHostSegment(int fg, int bg) : _fg(fg), _bg(bg) {
    if (auto host = std::getenv("HOSTNAME"))
        _hostName = host;
}

std::string SshHostSegment::get() const {
    return _hostName;
}
