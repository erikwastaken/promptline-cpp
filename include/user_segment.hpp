#ifndef PROMPTLINE_USER_SEGMENT_HPP
#define PROMPTLINE_USER_SEGMENT_HPP

#include "segment.hpp"


class UserSegment : public Segment {
    public:
        UserSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return false; };
    private:
        std::string _user {};
        const Segment *_next {nullptr};
};

#endif

