#ifndef INC_4_2_RUNGEKUTTAMETHOD_H
#define INC_4_2_RUNGEKUTTAMETHOD_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


vector<double> RungeKuttaMethods(double from, double to,
                                 double h,
                                 double y10, double y20,
                                 double (*F)(double, double, double)) {
    vector<double> xs, ys, zs;

    ys.push_back(y10);
    zs.push_back(y20);

    vector<double> k(4), l(4);

    int32_t step = 0;

    for (double x = from; x < to; x += h) {

        double prevX = x;
        double prevY = ys.back();
        double prevZ = zs.back();

        //fill K and L vectors
        k[0] = h * prevZ;
        l[0] = h * F(prevX, prevY, prevZ);

        k[1] = h * (prevZ + 0.5 * l[0]);
        l[1] = h * F(prevX + 0.5 * h, prevY + 0.5 * k[0], prevZ + 0.5 * l[0]);

        k[2] = h * (prevZ + 0.5 * l[1]);
        l[2] = l[1] = h * F(prevX + 0.5 * h, prevY + 0.5 * k[1], prevZ + 0.5 * l[1]);

        k[3] = h * (prevZ + l[2]);
        l[3] = h * F(prevX + h, prevY + k[2], prevZ + l[2]);

        double deltaY = (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
        double deltaZ = (l[0] + 2 * l[1] + 2 * l[2] + l[3]) / 6;

        double y = prevY + deltaY;
        double z = prevZ + deltaZ;

        xs.push_back(x);
        ys.push_back(y);
        zs.push_back(z);

        ++step;
    }

    return ys;
}
#endif //INC_4_2_RUNGEKUTTAMETHOD_H
