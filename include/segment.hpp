#ifndef POWERLINEPP_SEGMENT_HPP
#define POWERLINEPP_SEGMENT_HPP

#include <string>
#include <iostream>


class Segment {
    public:
        Segment(int fg, int bg) : _fg(fg), _bg(bg) {};
        virtual ~Segment() {};
        virtual std::string get() const = 0;
        virtual int fg() const { return _fg; };
        virtual int bg() const { return _bg; };
        virtual void next(const Segment *n) = 0; 
        virtual const Segment* next() const = 0;
        virtual bool empty() const = 0;
    private:
        int _fg;
        int _bg;
};

std::ostream& operator<<(std::ostream& out, const Segment &s);

#endif

