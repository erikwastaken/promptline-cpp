#ifndef POWERLINEPP_PROMPT_HPP
#define POWERLINEPP_PROMPT_HPP

#include "segment.hpp"
#include "formatter.hpp"

class Prompt {
    public:
        explicit Prompt(const Segment *root, const Formatter* fmt);
        std::string left() const;
        std::string right() const;
        std::string arrowEnd(const Segment *seg, int fg) const;
        std::string rightArrowEnd(const Segment *seg) const;
    private:
        const Segment *_root;
        const Formatter* _fmt;
};

#endif

