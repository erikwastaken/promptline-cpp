CPPFLAGS= -O3 -Wall -Wextra -Werror -pedantic -std=c++20 -Iinclude -Ilib

VERSION_MAJOR=1
VERSION_MINOR=0

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: version powerline-cpp

version:
	echo "#define POWERLINEPP_VERSION_MAJOR $(VERSION_MAJOR)" > include/version.h
	echo "#define POWERLINEPP_VERSION_MINOR $(VERSION_MINOR)" >> include/version.h

powerline-cpp: $(OBJS)
	$(CXX) $^ -o $@

install: powerline-cpp
	$(RM) /usr/local/bin/powerline-cpp
	cp powerline-cpp /usr/local/bin

clean:
	$(RM) $(OBJS) powerline-cpp
