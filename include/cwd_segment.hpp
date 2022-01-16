#ifndef POWERLINEPP_CWD_SEGMENT_HPP
#define POWERLINEPP_CWD_SEGMENT_HPP

#include "segment.hpp"

class CwdSegment : public Segment {
    public:
        CwdSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return false; };
    private:
        std::string _cwd {};
        int _fg;
        int _bg;
        const Segment *_next {nullptr};
};

#endif

