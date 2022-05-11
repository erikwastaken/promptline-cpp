cmake_minimum_required(VERSION 3.10)

project(promptline-cpp VERSION 1.1.10)
configure_file(version.hpp.in ../include/version.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(promptline-cpp src/main.cpp src/config.cpp src/config_parser.cpp src/cwd_segment.cpp src/git_segment.cpp src/prompt.cpp src/rc_segment.cpp src/segment.cpp src/time_segment.cpp src/user_segment.cpp src/virtualenv_segment.cpp src/ssh_host_segment.cpp)
target_include_directories(promptline-cpp PUBLIC include)

install(TARGETS promptline-cpp)
