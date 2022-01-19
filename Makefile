CPPFLAGS= -O3 -Wall -Wextra -Werror -pedantic -std=c++20 -Iinclude -Ilib

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: powerline-cpp

powerline-cpp: $(OBJS)
	$(CXX) $^ -o $@

clean:
	$(RM) $(OBJS) powerline-cpp
