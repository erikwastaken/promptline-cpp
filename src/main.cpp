#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>
#include "user_segment.hpp"
#include "cwd_segment.hpp"
#include "git_segment.hpp"
#include "rc_segment.hpp"
#include "virtualenv_segment.hpp"
#include "ssh_host_segment.hpp"
#include "prompt.hpp"
#include "formatter.hpp"
#include "zsh_formatter.hpp"
#include "bash_formatter.hpp"
#include "config.hpp"

// expects error code of last command as first parameter
// expects path to config file as second parameter
int main(int argc, char* argv[]) {
    if (argc < 2)
        return 1;

    std::unique_ptr<Formatter> fmt;
    if (auto shell = std::getenv("SHELL")) {
        if (std::string(shell).find("zsh") == std::string::npos)
            fmt = std::make_unique<BashFormatter>();
        else
            fmt = std::make_unique<ZshFormatter>();
    } else {
        return 1;
    }
    
    const auto config = argc == 3 ? Config(argv[2]) : Config();
    auto user_seg = UserSegment(config.fg("user"), config.bg("user"));
    auto cwd_seg = CwdSegment(config.fg("cwd"), config.bg("cwd"), fmt.get());
    auto git_seg = GitSegment(config.fg("git"), config.bg("git"), fmt.get());
    auto rc = std::atoi(argv[1]);
    auto rc_seg = RcSegment(config.fg("exit-code"), config.bg("exit-code"), rc);
    auto venv_seg = VenvSegment(config.fg("virtual-environment"), config.bg("virtual-environment"));
    auto ssh_seg = SshHostSegment(config.fg("ssh"), config.bg("ssh"));

    rc_seg.next(&ssh_seg);
    ssh_seg.next(&user_seg);
    user_seg.next(&venv_seg);
    venv_seg.next(&git_seg);
    git_seg.next(&cwd_seg);

    auto prompt = Prompt(&rc_seg, fmt.get());
    std::cout << prompt.left() << " ";
    return 0;
}
