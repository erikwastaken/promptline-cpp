#include "prompt.hpp"
#include "arrows.hpp"

Prompt::Prompt(const Segment *root) : _root(root) {}

std::string Prompt::left() const {
    auto current = _root;
    auto result = std::string();
    while (current != nullptr) {
        if (current->empty()) {
            current = current->next();
            continue;
        }
        result += arrows::arrow_start(current->fg(), current->bg());
        result += current->get();
        //result += (current->next() == nullptr) ? arrows::last_arrow_end(current->bg()) : arrows::arrow_end(current->bg(), current->next()->bg());
        result += arrowEnd(current, current->bg());
        current = current->next();
    }
    return result;
}

std::string Prompt::arrowEnd(const Segment *seg, int fg) const {
    if (seg->next() == nullptr)
        return arrows::last_arrow_end(fg);
    if (seg->next()->empty())
        return arrowEnd(seg->next(), fg);
    return arrows::arrow_end(fg, seg->next()->bg());
}
