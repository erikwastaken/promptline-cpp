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
#include "config_parser.hpp"

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
    
    auto config = argc == 3 ? ConfigParser(argv[2]).config() : std::unordered_map<std::string, std::pair<int,int>>();

    // create default segments and overwrite them with config if available
    auto user_seg = UserSegment(255, 31);
    if (config.contains("user"))
        user_seg = UserSegment(config["user"].first, config["user"].second);
    auto cwd_seg = CwdSegment(255, 241, fmt.get());
    if (config.contains("user"))
        cwd_seg = CwdSegment(config["cwd"].first, config["cwd"].second, fmt.get());
    auto git_seg = GitSegment(255, 238, fmt.get());
    if (config.contains("user"))
        git_seg = GitSegment(config["git"].first, config["git"].second, fmt.get());
    auto rc = std::atoi(argv[1]);
    auto rc_seg = RcSegment(255, 88, rc);
    if (config.contains("user"))
        rc_seg = RcSegment(config["exit-code"].first, config["exit-code"].second, rc);
    auto venv_seg = VenvSegment(255, 38);
    if (config.contains("user"))
        venv_seg = VenvSegment(config["virtual-environment"].first, config["virtual-environment"].second);
    auto ssh_seg = SshHostSegment(255,208);
    if (config.contains("user"))
        ssh_seg = SshHostSegment(255,208);

    rc_seg.next(&ssh_seg);
    ssh_seg.next(&user_seg);
    user_seg.next(&venv_seg);
    venv_seg.next(&git_seg);
    git_seg.next(&cwd_seg);

    auto prompt = Prompt(&rc_seg, fmt.get());
    std::cout << prompt.left() << " ";
    return 0;
}
