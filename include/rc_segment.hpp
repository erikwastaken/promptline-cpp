#ifndef POWERLINEPP_RC_SEGMENT_HPP
#define POWERLINEPP_RC_SEGMENT_HPP

#include "segment.hpp"

class RcSegment : public Segment {
    public:
        RcSegment(int fg, int bg, int rc);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return _rc == 0; };
    private:
        int _fg;
        int _bg;
        int _rc;
        const Segment *_next {nullptr};
};

#endif

