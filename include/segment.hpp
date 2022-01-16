#ifndef POWERLINEPP_SEGMENT_HPP
#define POWERLINEPP_SEGMENT_HPP

#include <string>
#include <iostream>


class Segment {
    public:
        virtual ~Segment() {};
        virtual std::string get() const = 0;
        virtual int fg() const = 0;
        virtual int bg() const = 0;
        virtual void next(const Segment *n) = 0; 
        virtual const Segment* next() const = 0;
        virtual bool empty() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Segment &s);

#endif

