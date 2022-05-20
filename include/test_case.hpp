#ifndef PROMPTLINE_TEST_CASE_HPP
#define PROMPTLINE_TEST_CASE_HPP

#include <string>
#include <iostream>

namespace test {
    class TestCase {
        public:
            TestCase(const std::string& name) : _name(name) {
                std::cout << _name << ": ";
            };

            void print_failure(const std::string msg) {
                std::cout << "\x1b[31m" << "failed! " << msg << "\x1b[0m" << '\n';
            }
            void print_success() {
                std::cout << "\x1b[32m" << "passed" << "\x1b[0m" << '\n';
            }

            template<typename T>
            int assert_equals(T exp, T act, std::string msg = "Test failed!") {
                if (exp == act) {
                    print_success();
                    return 0;
                }
                print_failure(msg);
                return 1;

            }
        private:
            std::string _name {};
    };
}
#endif
