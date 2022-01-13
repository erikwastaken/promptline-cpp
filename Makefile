CPPFLAGS= -g -Wall -Wextra -Werror -pedantic -std=c++20 -Iinclude -Ilib

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))
TESTS=$(wildcard test/*.cpp)
TOBJS=$(subst .cpp,.o,$(TESTS))
SUT=$(filter-out src/edit.o,$(OBJS))

all: suite powerlinepp

powerlinepp: $(OBJS)
	$(CXX) $^ -o $@

suite: $(TOBJS) $(SUT)
	$(CXX) $^ -o $@

clean:
	$(RM) $(OBJS) $(TOBJS) powerlinepp suite
