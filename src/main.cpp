#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>
#include <cstring>
#include <vector>
#include "segment.hpp"
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
#include "version.hpp"

bool leftPrompt(int argc, char* argv[]) {
    if (argc == 2) return true;
    for (auto i=0; i != argc; ++i) {
        if (strcmp(argv[i], "--right") == 0)
            return false;
    }
    return true;
}

std::unique_ptr<Segment> make_segment(const std::string &segment_name, const Config* config, Formatter* fmt, int rc) {
    int fg = config->fg(segment_name);
    int bg = config->bg(segment_name);
    if (segment_name == "user") return std::make_unique<UserSegment>(fg, bg);
    else if (segment_name == "cwd") return std::make_unique<CwdSegment>(fg, bg, fmt);
    else if (segment_name == "git") return std::make_unique<GitSegment>(fg, bg, fmt);
    else if (segment_name == "exit-code") return std::make_unique<RcSegment>(fg, bg, rc);
    else if (segment_name == "virtual-environment") return std::make_unique<VenvSegment>(fg, bg);
    else if (segment_name == "ssh") return std::make_unique<SshHostSegment>(fg, bg, fmt);
    else if (segment_name == "time") return std::make_unique<TimeSegment>(fg, bg);
    else return nullptr;
}

void print_version() {
    std::cout << "Current version: "
              << PROMPTLINE_VERSION_MAJOR
              << "."
              << PROMPTLINE_VERSION_MINOR
              << "."
              << PROMPTLINE_VERSION_PATCH
              << '\n';
}

std::unique_ptr<Formatter> make_formatter() {
    if (auto shell = std::getenv("SHELL")) {
        if (std::string(shell).find("zsh") == std::string::npos)
            return std::make_unique<BashFormatter>();
        else
            return std::make_unique<ZshFormatter>();
    } else {
        return nullptr;
    }
}

// expects error code of last command as first parameter
// expects path to config file as second parameter
int main(int argc, char* argv[]) {

    if (argc < 2) {
        print_version();
        return 0;
    }

    std::unique_ptr<Formatter> fmt = make_formatter();
    if (fmt == nullptr)
        return 1;

    const auto config = Config();
    auto rc = std::atoi(argv[1]);

    // TODO refactor to remove doubled code
    // left hand side
    if (leftPrompt(argc, argv)) {
        std::vector<std::unique_ptr<Segment>> segments {};
        for (auto seg : config.left_segments()) {
            segments.push_back(make_segment(seg, &config, fmt.get(), rc));
        }
        auto head = segments[0].get();
        auto current = head;
        for (auto i=1ul; i!=segments.size(); ++i) {
            current->next(segments[i].get());
            current = segments[i].get();
        }
        auto prompt = Prompt(head, fmt.get());
        prompt.left(std::cout);
        return 0;
    }

    // right hand side
    std::vector<std::unique_ptr<Segment>> segments {};
    for (auto seg : config.right_segments()) {
        segments.push_back(make_segment(seg, &config, fmt.get(), rc));
    }
    auto head = segments[0].get();
    auto current = head;
    for (auto i=1ul; i!=segments.size(); ++i) {
        current->next(segments[i].get());
        current = segments[i].get();
    }
    auto prompt = Prompt(head, fmt.get());
    prompt.right(std::cout);
    return 0;
}
