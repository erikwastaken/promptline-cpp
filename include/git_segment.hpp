#ifndef POWERLINEPP_GIT_SEGMENT_HPP
#define POWERLINEPP_GIT_SEGMENT_HPP

#include "segment.hpp"
#include "formatter.hpp"

class GitSegment : public Segment {
    public:
        GitSegment(int fg, int bg, const Formatter* fmt);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return get().empty(); };
    private:
        class Command {
            public:
                Command(const std::string &cmd);
                std::string output() const { return _out; };
            private:
                std::string _out {};
        };
        std::string _branch {};
        int _fg;
        int _bg;
        const Segment *_next {nullptr};
};

#endif

