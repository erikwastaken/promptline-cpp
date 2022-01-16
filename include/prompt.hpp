#ifndef POWERLINEPP_PROMPT_HPP
#define POWERLINEPP_PROMPT_HPP

#include "segment.hpp"

class Prompt {
    public:
        explicit Prompt(const Segment *root);
        std::string left() const;
        std::string arrowEnd(const Segment *seg, int fg) const;
    private:
        const Segment *_root;
};

#endif

