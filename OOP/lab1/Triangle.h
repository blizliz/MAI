#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Figure.h"

class Triangle : public Figure{
public:
    Triangle();
    Triangle(std::istream &is);

    double Square() override;
    void   Print() override;

    virtual ~Triangle();
private:
    std::string side_sa;
    std::string side_sb;
    std::string side_sc;
    size_t side_a = 0;
    size_t side_b = 0;
    size_t side_c = 0;
};

#endif

