#ifndef HEXAGON_H
#define	HEXAGON_H

#include <iostream>
#include <cstring>
#include "Figure.h"

class Hexagon : public Figure {
public:
	Hexagon();
	Hexagon(size_t i);

	Hexagon& operator=(const Hexagon& right);
	friend bool operator==(const Hexagon& left, const Hexagon& right);
	friend std::ostream& operator<<(std::ostream& os, const Hexagon& obj);

	double Square();
	void Print() override;

	virtual ~Hexagon();
private:
	size_t side_a;
};

#endif
