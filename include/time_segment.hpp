#ifndef POWERLINEPP_TIME_SEGMENT_HPP
#define POWERLINEPP_TIME_SEGMENT_HPP

#include "segment.hpp"
#include <chrono>

class TimeSegment : public Segment {
    public:
        TimeSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return false; };
    private:
        int _fg;
        int _bg;
        const Segment *_next {nullptr};
};

#endif

