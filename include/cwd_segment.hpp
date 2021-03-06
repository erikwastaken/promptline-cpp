#ifndef PROMPTLINE_CWD_SEGMENT_HPP
#define PROMPTLINE_CWD_SEGMENT_HPP

#include "segment.hpp"
#include "formatter.hpp"

class CwdSegment : public Segment {
    public:
        CwdSegment(int fg, int bg, const Formatter* fmt);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return false; };
    private:
        std::string _cwd {};
        const Segment *_next {nullptr};
};

#endif

