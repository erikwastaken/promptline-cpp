#include "prompt.hpp"
#include "arrows.hpp"

Prompt::Prompt(const Segment *root) : _root(root) {}

std::string Prompt::left() const {
    auto current = _root;
    auto result = std::string();
    while (current != nullptr) {
        result += arrows::arrow_start(current->fg(), current->bg());
        result += current->get();
        result += (current->next() == nullptr) ? arrows::last_arrow_end(current->bg()) : arrows::arrow_end(current->bg(), current->next()->bg());
        current = current->next();
    }
    return result;
}
