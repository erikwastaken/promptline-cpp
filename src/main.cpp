#include <iostream>
#include <cstdlib>
#include "user_segment.hpp"
#include "cwd_segment.hpp"
#include "git_segment.hpp"
#include "rc_segment.hpp"
#include "prompt.hpp"

// expects error code of last command as first parameter
int main(int argc, char* argv[]) {
    if (argc < 2)
        return 1;
    auto user_seg = UserSegment(255, 31);
    auto cwd_seg = CwdSegment(255, 241);
    auto git_seg = GitSegment(255, 238);
    if (git_seg.empty()) {
        user_seg.next(&cwd_seg);
    } else {
        user_seg.next(&git_seg);
        git_seg.next(&cwd_seg);
    }
    Segment* root;
    if (std::atoi(argv[1]) != 0) {
        auto rc_seg = RcSegment(255,88);
        rc_seg.next(&user_seg);
        root = &rc_seg;
    } else {
        root = &user_seg;
    }
    auto prompt = Prompt(root);
    std::cout << prompt.left() << " ";
    return 0;
}
