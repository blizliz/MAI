#include "stdafx.h"
#include "Octagon.h"
#include <iostream>
#include <cmath>
#include "Figure.h"


Octagon::Octagon() : Octagon(0) {
}

Octagon::Octagon(size_t i) : side_a(i) {
	//std::cout << "Octagon created: " << side_a << std::endl;
}

Octagon& Octagon::operator=(const Octagon& right) {

	if (this == &right) return *this;

	//std::cout << "Octagon copied" << std::endl;

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