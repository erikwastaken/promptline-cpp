#include "git_segment.hpp"
#include <fstream>
#include <cstdlib>
#include <filesystem>

GitSegment::GitSegment(int fg, int bg, const Formatter* fmt) : Segment(fg,bg) {
    auto out = Command("git rev-parse --abbrev-ref HEAD").output();
    if (out.empty())
        return;
    _branch += fmt->reset() + fmt->fgColor(fg) + fmt->bgColor(bg);
    _branch += "\ue0a0";
    _branch += " ";
    _branch += out;
    _branch += fmt->boldOn();
}

std::string GitSegment::get() const {
    return _branch;
}

GitSegment::Command::Command(const std::string &cmd) {
    auto tmp_path = std::filesystem::temp_directory_path();
    tmp_path /= "powerlinepp_git_command.txt";
    // redirect cout into temporary file
    auto command = cmd + " > " + tmp_path.string();
    // ignore cerr
    command += " 2> /dev/null";
    std::system(command.c_str());
    auto fs = std::fstream(tmp_path.string());
    if (!fs.is_open())
        throw std::runtime_error("file not open");
    std::getline(fs, _out);
    fs.close();
}
