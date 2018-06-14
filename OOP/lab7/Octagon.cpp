#include "Octagon.h"
#include <iostream>
#include <cmath>
#include "Figure.h"


Octagon::Octagon() : Octagon(0) {
}

Octagon::Octagon(size_t i) : side_a(i) {
	if(side_a < 0) {
		std::cout << "Can't create octagon with negative side value" << std::endl;
		side_a = 0;
	} else {
		std::cout << "Octagon created: " << side_a << std::endl;
	}
}

Octagon::Octagon(const Octagon& orig) {
	std::cout << "Triangle copy created" << std::endl;
	side_a = orig.side_a;
}


Octagon& Octagon::operator=(const Octagon& right) {

	if (this == &right) return *this;
	side_a = right.side_a;

	return *this;
}

bool operator==(const Octagon& left, const Octagon& right) {
	return left.side_a == right.side_a;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
	std::cout << "Octagon: ";
	os << "a=" << obj.side_a;
	return os;
}

std::istream & operator >>(std::istream &is, Octagon &obj) {
	std::cout << "Enter side: ";
	is >> obj.side_a;
	return is;
}

double Octagon::Square() {
	return (3 * sqrt(3) * side_a * side_a) / 2.0;
}

void Octagon::Print() {
	std::cout << "Octagon: ";
	std::cout << "a = " << side_a;
}

Octagon::~Octagon() {
	//std::cout << "Octagon deleted" << std::endl;
}