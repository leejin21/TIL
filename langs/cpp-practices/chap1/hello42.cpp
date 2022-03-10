#include <iostream>

int main()
{
    int i1 = 2;
    int i2, i3 = 5;
    // float pi = 3.141592;
    double x = -1.5e6;          // -1.5 * 10^6, 지수
    double y = -1.5e-6;         // -1.5 * 10^-6, 소수
    char c1 = 'a', c2 = 35;     // 'a' != "a"
    // bool cmp = i1<pi, happy = true;

    const double pi = 3.14;

    std::string s2 = "In C++ better like this\n"
                    "this is too long for one line";

    std::cout << "The answer to the Ultimate Q of Life, \n"
            << "the Universe, and Everything is: "
            << std::endl << s2 << std::endl;

    std::cout << "pi is " << pi << "." << std::endl;

    return 0;
}