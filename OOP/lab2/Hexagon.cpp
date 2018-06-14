#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() : Hexagon(0){
    //std::cout << "Hexagon created: " << std::endl;
}

Hexagon::Hexagon(size_t i) : side(i) {
	if (side < 0) {
		std::cout << "Can't create hexagon with negative side value" << std::endl;
		side = 0;
	}
	else {
		std::cout << "Hexagon created: " << side << std::endl;
	}
}

std::istream& operator >>(std::istream &is, Hexagon &obj)
{
	std::cout << "Enter side: ";
	is >> obj.side;
	return is;
}


 Hexagon& Hexagon::operator=(const Hexagon& right) {
    
	 if (this == &right) return *this;

	 side = right.side;

	 return *this;
 }

 bool Hexagon::operator ==(const Hexagon &obj) const
 {
	 return side == obj.side;
 }

 std::ostream& operator <<(std::ostream &os, const Hexagon &obj)
 {
	 os << "Hexagon: " << obj.side;
	 return os;
 }

 void Hexagon::Print() {
	 std::cout << "Hexagon: ";
	 std::cout << "a = " << side;

 }

 double Hexagon::Square() {
	 return (3 * sqrt(3) * side * side) / 2.0;
 }


Hexagon::~Hexagon() {
    std::cout << "Hexagon deleted" << std::endl;
}