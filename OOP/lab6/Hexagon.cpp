#include "Hexagon.h"
#include <iostream>
#include <cmath>
#include "Figure.h"


Hexagon::Hexagon() : Hexagon(0) {
}

Hexagon::Hexagon(size_t i) : side_a(i) {
	//std::cout << "Hexagon created: " << side_a << std::endl;
}

Hexagon::Hexagon(const Hexagon& orig) {
	std::cout << "Triangle copy created" << std::endl;
	side_a = orig.side_a;
}


Hexagon& Hexagon::operator=(const Hexagon& right) {

	if (this == &right) return *this;

	//std::cout << "Hexagon copied" << std::endl;

	side_a = right.side_a;

	return *this;
}

bool operator==(const Hexagon& left, const Hexagon& right) {
	return left.side_a == right.side_a;
}

std::ostream& operator<<(std::ostream& os, const Hexagon& obj) {
	std::cout << "Hexagon: ";
	os << "a=" << obj.side_a;
	return os;
}

double Hexagon::Square() {
	return (3 * sqrt(3) * side_a * side_a) / 2.0;
}

void Hexagon::Print() {
	std::cout << "Hexagon: ";
	std::cout << "a = " << side_a;
}

Hexagon::~Hexagon() {
	//std::cout << "Hexagon deleted" << std::endl;
}