#ifndef HEXAGON_H
#define	HEXAGON_H

#include <iostream>
#include <string>
#include "Figure.h"

class Hexagon : public Figure{
public:
    Hexagon();
	Hexagon(size_t i);
	friend std::istream& operator >>(std::istream &is, Hexagon &obj);
    Hexagon& operator=(const Hexagon& right);
	bool operator ==(const Hexagon &obj) const;
	friend std::ostream& operator <<(std::ostream &os, const Hexagon &obj);

    double Square() override;
    void   Print() override;

    virtual ~Hexagon();
private:
    size_t side;
};

#endif
