#include <iostream>
#include <cstdlib>

int main() {
    auto o = std::system("pyenv version");
    if (o) {
        std::cout << o << '\n';
        return 0;
    }
    return 1;
}
