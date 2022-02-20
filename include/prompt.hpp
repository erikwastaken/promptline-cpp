#ifndef POWERLINEPP_PROMPT_HPP
#define POWERLINEPP_PROMPT_HPP

#include "segment.hpp"
#include "formatter.hpp"
#include <iostream>

class Prompt {
    public:
        explicit Prompt(const Segment *root, const Formatter* fmt);
        std::string left() const;
        void left(std::ostream &os) const;
        std::string right() const;
        void right(std::ostream &os) const;
        std::string arrowEnd(const Segment *seg, int fg) const;
        std::string rightArrowEnd(const Segment *seg) const;
    private:
        const Segment *_root;
        const Formatter* _fmt;
};

#endif

