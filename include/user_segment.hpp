#ifndef POWERLINEPP_USER_SEGMENT_HPP
#define POWERLINEPP_USER_SEGMENT_HPP

#include "segment.hpp"


class UserSegment : public Segment {
    public:
        UserSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
    private:
        std::string _user {};
        int _fg;
        int _bg;
        const Segment *_next {nullptr};
};

#endif

