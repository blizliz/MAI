#ifndef HEXAGON_H
#define	HEXAGON_H

#include <iostream>
#include <string>
#include "Figure.h"

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(std::istream &is);

    double Square() override;
    void   Print() override;

    virtual ~Hexagon();
private:
    std::string side_sa;
    size_t side_a = 0;
};

#endif
