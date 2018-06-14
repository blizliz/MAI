#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() {
    std::cout << "Hexagon created: " << std::endl;
}


Hexagon::Hexagon(std::istream &is) {
        std::cout << "Enter the side of Hexagon: ";

        is >> side_sa;
        
        for (int i = 0; i < side_sa.length(); i++) {
            if (!isalpha(side_sa[i])) {
                side_a = 10 * side_a + side_sa[i] - 0x30;
            }
        }
}

double Hexagon::Square() {
    return (3 * sqrt(3) * side_a * side_a) / 2.0;
}

void Hexagon::Print() {
    std::cout << "Hexagon:" << std::endl;
    std::cout << "a = " << side_a << std::endl;
}

Hexagon::~Hexagon() {
    std::cout << "Hexagon deleted" << std::endl;
}