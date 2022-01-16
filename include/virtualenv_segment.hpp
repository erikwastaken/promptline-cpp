#ifndef POWERLINEPP_VIRTUALENV_SEGMENT
#define POWERLINEPP_VIRTUALENV_SEGMENT

#include "segment.hpp"

class VenvSegment : public Segment {
    public:
        VenvSegment(int fg, int bg);
        virtual std::string get() const override;
        virtual int fg() const override { return _fg; };
        virtual int bg() const override { return _bg; };
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return _env.empty(); };
    private:
        int _fg;
        int _bg;
        std::string _env {};
        const Segment *_next {nullptr};
};

#endif

