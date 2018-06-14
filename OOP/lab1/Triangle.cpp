#include "Triangle.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

Triangle::Triangle() {
    std::cout << "Triangle created: " << std::endl;
}

Triangle::Triangle(std::istream &is) {
    std::cout << "Set first side: ";
    is >> side_sa;

    for (int i = 0; i < side_sa.length(); i++) {
        if (!isalpha(side_sa[i])) {
            side_a = 10 * side_a + side_sa[i] - 0x30;
        }
    }

    std::cout << "Set second side: ";
    is >> side_sb;

    for (int i = 0; i < side_sb.length(); i++) {
        if (!isalpha(side_sb[i])) {
            side_b += 10 * side_b + side_sb[i] - 0x30;
        }
    }

    std::cout << "Set third side: ";
    is >> side_sc;

    for (int i = 0; i < side_sc.length(); i++) {
        if (!isalpha(side_sc[i])) {
            side_c += 10 * side_c + side_sc[i] - 0x30;
        }
    }
}

double Triangle::Square()
{
    double p = double(side_a + side_b + side_c) / 2.0;
    return sqrt(p * (p - double(side_a)) * (p - double(side_b)) * (p - double(side_c)));
}

void Triangle::Print()
{
    std::cout << "a = " << side_a << ", b = " << side_b << ", c = " << side_c << std::endl;
}

Triangle::~Triangle()
{
    std::cout << "Triangle deleted" << std::endl;
}
