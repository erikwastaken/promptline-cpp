#include "prompt.hpp"

Prompt::Prompt(const Segment *root, const Formatter* fmt) : _root(root), _fmt(fmt) {}

std::string Prompt::left() const {
    auto current = _root;
    auto result = std::string();
    while (current != nullptr) {
        if (current->empty()) {
            current = current->next();
            continue;
        }
        result += _fmt->arrow_start(current->fg(), current->bg());
        result += current->get();
        result += arrowEnd(current, current->bg());
        current = current->next();
    }
    return result;
}

std::string Prompt::arrowEnd(const Segment *seg, int fg) const {
    if (seg->next() == nullptr)
        return _fmt->last_arrow_end(fg);
    if (seg->next()->empty())
        return arrowEnd(seg->next(), fg);
    return _fmt->arrow_end(fg, seg->next()->bg());
}
