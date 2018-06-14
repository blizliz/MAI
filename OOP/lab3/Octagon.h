#ifndef OCTAGON_H
#define	OCTAGON_H

#include <iostream>
#include <cstring>
#include "Figure.h"

class Octagon : public Figure {
public:
	Octagon();
	Octagon(size_t i);

	Octagon& operator=(const Octagon& right);
	friend bool operator==(const Octagon& left, const Octagon& right);
	friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);

	double Square();
	void Print() override;

	virtual ~Octagon();
private:
	size_t side_a;
};

#endif
