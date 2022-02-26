#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>
#include <cstring>
#include "user_segment.hpp"
#include "cwd_segment.hpp"
#include "git_segment.hpp"
#include "rc_segment.hpp"
#include "virtualenv_segment.hpp"
#include "ssh_host_segment.hpp"
#include "time_segment.hpp"
#include "prompt.hpp"
#include "formatter.hpp"
#include "zsh_formatter.hpp"
#include "bash_formatter.hpp"
#include "config.hpp"
#include "version.h"

bool leftPrompt(int argc, char* argv[]) {
    if (argc == 2) return true;
    for (auto i=0; i != argc; ++i) {
        if (strcmp(argv[i], "--right") == 0)
            return false;
    }
    return true;
}

// expects error code of last command as first parameter
// expects path to config file as second parameter
int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Current version: " << POWERLINEPP_VERSION_MAJOR << "." << POWERLINEPP_VERSION_MINOR << '\n';
        return 0;
    }

    std::unique_ptr<Formatter> fmt;
    if (auto shell = std::getenv("SHELL")) {
        if (std::string(shell).find("zsh") == std::string::npos)
            fmt = std::make_unique<BashFormatter>();
        else
            fmt = std::make_unique<ZshFormatter>();
    } else {
        return 1;
    }

    const auto config = Config();
    if (leftPrompt(argc, argv)) {
        auto user_seg = UserSegment(config.fg("user"), config.bg("user"));
        auto cwd_seg = CwdSegment(config.fg("cwd"), config.bg("cwd"), fmt.get());
        auto git_seg = GitSegment(config.fg("git"), config.bg("git"), fmt.get());
        auto rc = std::atoi(argv[1]);
        auto rc_seg = RcSegment(config.fg("exit-code"), config.bg("exit-code"), rc);
        auto venv_seg = VenvSegment(config.fg("virtual-environment"), config.bg("virtual-environment"));
        auto ssh_seg = SshHostSegment(config.fg("ssh"), config.bg("ssh"), fmt.get());

        rc_seg.next(&ssh_seg);
        ssh_seg.next(&user_seg);
        user_seg.next(&venv_seg);
        venv_seg.next(&git_seg);
        git_seg.next(&cwd_seg);
        auto prompt = Prompt(&rc_seg, fmt.get());
        prompt.left(std::cout);
        return 0;
    }

    auto time_seg = TimeSegment(config.fg("time"), config.bg("time"));
    auto prompt = Prompt(&time_seg, fmt.get());
    prompt.right(std::cout);
    return 0;
}
