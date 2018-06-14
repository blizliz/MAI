#include "stdafx.h"
#include "Triangle.h"
#include <iostream>

Triangle::Triangle() : Triangle(0, 0, 0) {
	std::cout << "Triangle created: default" << std::endl;
}

Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {
	std::cout << "Triangle created: " << side_a << ", " << side_b << ", " << side_c << std::endl;
}

Triangle::Triangle(const Triangle& orig) {
	std::cout << "Triangle copy created" << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_c = orig.side_c;
}

Triangle& Triangle::operator=(const Triangle& right) {

	if (this == &right) return *this;

	std::cout << "Triangle copied" << std::endl;
	side_a = right.side_a;
	side_b = right.side_b;
	side_c = right.side_c;

	return *this;
}

bool operator==(const Triangle& left, const Triangle& right) {
	return(left.side_a == right.side_a
		&& left.side_b == right.side_b
		&& left.side_b == right.side_b);
}

//std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
//	std::cout << "Triangle: ";
//	os << "a=" << obj.side_a << ", b=" << obj.side_b << ", c=" << obj.side_c;
//	return os;
//}

void Triangle::Print() {
	std::cout << "Triangle: ";
	std::cout << "a = " << side_a << ", b = " << side_b << ", c = " << side_c;
}

Triangle::~Triangle() {
	//std::cout << "Triangle deleted" << std::endl;
}
