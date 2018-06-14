#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon () {
    std::cout << "Octagon created: " << std::endl;
}

Octagon::Octagon(std::istream &is) {
    std::cout << "Enter the side of Octagon: ";
    
            is >> side_sa;
            
            for (int i = 0; i < side_sa.length(); i++) {
                if (!isalpha(side_sa[i])) {
                    side_a = 10 * side_a + side_sa[i] - 0x30;
                }
            }
}

double Octagon::Square() {
    return 2.0 * side_a * side_a * (1.0 + sqrt(2));
}

void Octagon::Print() {
    std::cout << "Hexagon:" << std::endl;
    std::cout << "a = " << side_a << std::endl;
}

Octagon::~Octagon() {
    std::cout << "Octagon deleted" << std::endl;
}