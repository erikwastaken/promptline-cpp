#ifndef POWERLINEPP_RC_SEGMENT_HPP
#define POWERLINEPP_RC_SEGMENT_HPP

#include "segment.hpp"

class RcSegment : public Segment {
    public:
        RcSegment(int fg, int bg, int rc);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return _rc == 0; };
    private:
        int _rc;
        const Segment *_next {nullptr};
};

#endif

