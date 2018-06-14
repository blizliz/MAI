#ifndef FIGURE_H
#define	FIGURE_H

#include <iostream>

class Figure {
public:
	virtual void Print() = 0;
	virtual double Square() = 0;
	bool operator < (Figure &rht) {
		return Square() < rht.Square();
	}
	friend std::ostream& operator <<(std::ostream& os, Figure &obj) {
		obj.Print();
		return os;
	}
	virtual ~Figure() {};
};

#endif	/* FIGURE_H */

