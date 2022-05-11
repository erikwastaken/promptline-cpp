#ifndef PROMPTLINE_VIRTUALENV_SEGMENT
#define PROMPTLINE_VIRTUALENV_SEGMENT

#include "segment.hpp"

class VenvSegment : public Segment {
    public:
        VenvSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return _env.empty(); };
    private:
        std::string _env {};
        const Segment *_next {nullptr};
};

#endif

