#ifndef POWERLINEPP_SSH_HOST_HPP
#define POWERLINEPP_SSH_HOST_HPP

#include "segment.hpp"
#include "formatter.hpp"

class SshHostSegment : public Segment {
    public:
        SshHostSegment(int fg, int bg, Formatter* fmt);
        virtual std::string get() const override;
        virtual void next(const Segment *n) override { _next = n; };
        virtual const Segment* next() const override { return _next; };
        virtual bool empty() const override { return get().empty(); };
    private:
        std::string _hostName {};
        const Segment *_next {nullptr};
};

#endif

