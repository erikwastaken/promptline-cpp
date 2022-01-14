#include <iostream>
#include <cstdlib>
#include "segment.hpp"

std::string static user() {
    return "%n";
}

std::string static cwd() {
    return "%0~";
}

std::string static last_rc(const Segment* next=nullptr) {
    // X.Y.Z is the zsh/bash ternary; if X then Y else Z
    if (next == nullptr)
        return "%(?.." + Segment::arrow_start(255,88) + "%?" + Segment::last_arrow_end(88) + ")";
    return "%(?.." + Segment::arrow_start(255,88) + "%?" + Segment::arrow_end(88, next->bg()) + ")";
}

int main() {
    auto user_seg = Segment(user(), 255, 31);
    auto cwd_seg = Segment(cwd(), 255, 241);
    user_seg.next(&cwd_seg);
    std::cout << last_rc(&user_seg) << user_seg << cwd_seg << " ";
    return 0;
}
