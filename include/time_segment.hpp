#ifndef PROMPTLINE_TIME_SEGMENT_HPP
#define PROMPTLINE_TIME_SEGMENT_HPP

#include "segment.hpp"
#include <chrono>

class TimeSegment : public Segment {
    public:
        TimeSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return false; };
    private:
        const Segment *_next {nullptr};
};

#endif

