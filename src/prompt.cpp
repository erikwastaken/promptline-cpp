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

void Prompt::left(std::ostream &os) const {
    auto current = _root;
    while (current != nullptr) {
        if (current->empty()) {
            current = current->next();
            continue;
        }
        os << _fmt->arrow_start(current->fg(), current->bg());
        os << current->get();
        os << arrowEnd(current, current->bg());
        current = current->next();
    }
    os << " ";
}

std::string Prompt::right() const {
    auto current = _root;
    auto result = std::string();
    while (current != nullptr) {
        if (current->empty()) {
            current = current->next();
            continue;
        }
        result += _fmt->right_arrow_start(current->fg(), current->bg());
        result += current->get();
        result += rightArrowEnd(current);
        current = current->next();
    }
    return result;
}

void Prompt::right(std::ostream &os) const {
    auto current = _root;
    auto result = std::string();
    while (current != nullptr) {
        if (current->empty()) {
            current = current->next();
            continue;
        }
        os << _fmt->right_arrow_start(current->fg(), current->bg());
        os << current->get();
        os << rightArrowEnd(current);
        current = current->next();
    }
}

std::string Prompt::arrowEnd(const Segment *seg, int fg) const {
    if (seg->next() == nullptr)
        return _fmt->last_arrow_end(fg);
    if (seg->next()->empty())
        return arrowEnd(seg->next(), fg);
    return _fmt->arrow_end(fg, seg->next()->bg());
}

std::string Prompt::rightArrowEnd(const Segment *seg) const {
    if (seg->next() == nullptr)
        return _fmt->right_last_arrow_end();
    if (seg->next()->empty())
        return rightArrowEnd(seg->next());
    return _fmt->right_arrow_end();
}
