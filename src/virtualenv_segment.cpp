#include "virtualenv_segment.hpp"
#include <cstdlib>
#include <filesystem>
#include <vector>

VenvSegment::VenvSegment(int fg, int bg) : _fg(fg), _bg(bg) {
    auto venv_types = std::vector<std::string>({"PYENV_VIRTUALENV", "VIRTUAL_ENV", "CONDA_ENV_PATH", "CONDA_DEFAULT_ENV"});
    for (auto venv : venv_types) {
        if( auto env = std::getenv(venv.c_str())) {
            auto path = std::filesystem::path(env);
            _env = *(--path.end());
            return;
        }
    }
}

std::string VenvSegment::get() const {
    return _env;
}
