CPPFLAGS= -O3 -Wall -Wextra -Werror -pedantic -std=c++20 -Iinclude -Ilib

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: powerline-cpp

powerline-cpp: $(OBJS)
	$(CXX) $^ -o $@

install: powerline-cpp
	$(RM) /usr/local/bin/powerline-cpp
	cp powerline-cpp /usr/local/bin

clean:
	$(RM) $(OBJS) powerline-cpp
