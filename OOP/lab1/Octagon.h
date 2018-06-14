#ifndef OCTAGON_H
#define	OCTAGON_H

#include <iostream>
#include <string>
#include "Figure.h"

class Octagon : public Figure {
public:
    Octagon();
    Octagon(std::istream &is);

    double Square() override;
    void   Print() override;

    virtual ~Octagon();
private:
    std::string side_sa;
    size_t side_a = 0;
};

#endif
