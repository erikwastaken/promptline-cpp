#ifndef POWERLINEPP_PROMPT_HPP
#define POWERLINEPP_PROMPT_HPP

#include "segment.hpp"

class Prompt {
    public:
        explicit Prompt(const Segment *root);
        std::string left() const;
    private:
        const Segment *_root;
};

#endif

