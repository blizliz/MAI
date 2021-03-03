#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

double FROM = 0;
double TO = 1;
double H = 0.2;
double X0 = 0;
double Y0 = 1;
double Z0 = 3;

double F(double x, double z) {
    return 2 * x * z / (x * x + 1);
}

double ExactF(double x) {
    return x * x * x + 3 * x + 1;
}

void EulerMethod(ofstream &logFile) {
    logFile << "\nEULER METOD:\n";
    vector<double> xs, ys, zs;

    xs.push_back(X0);
    ys.push_back(Y0);
    zs.push_back(Z0);

    logFile << 0 << ": "
            << "x = " << X0
            << ", y = "<< Y0
            << ", z = "<< Z0
            << ", y(exact) = " << ExactF(X0)
            << ", eps = " << fabs(ExactF(X0) - Y0) << "\n";

    int32_t step = 1;

    for (double x = FROM + H; x < TO; x += H) {
        double prevX = xs.back();
        double prevY = ys.back();
        double prevZ = zs.back();

        double y = prevY + H * prevZ;
        double z = prevZ + H * F(prevX, prevY);

        xs.push_back(x);
        ys.push_back(y);
        zs.push_back(z);

        double exactY = ExactF(x);
        double eps = fabs(exactY - z);

        logFile << step << ": "
                << "x = " << x
                << ", y = "<< y
                << ", z = "<< z
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n";

        ++step;
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs[i] << ", y" << i << " = " << ys[i] << "\n";
    }
}

void RungeKuttaMethods(ofstream &logFile) {
    logFile << "\nRUNGE-KUTTA METOD:\n";
    vector<double> xs, ys, zs;

    ys.push_back(Y0);
    zs.push_back(Z0);

    vector<double> k(4), l(4);

    int32_t step = 0;

    for (double x = FROM; x <= TO; x += H) {
        logFile << "_______________step #" << step << ":\n";
        double prevX = x;
        double prevY = ys.back();
        double prevZ = zs.back();

        //fill K and L vectors
        k[0] = H * prevZ;
        l[0] = H * F(prevX, prevZ);

        k[1] = H * (prevZ + 0.5 * l[0]);
        l[1] = H * F(prevX + 0.5 * H, prevZ + 0.5 * l[0]);

        k[2] = H * (prevZ + 0.5 * l[1]);
        l[2] = l[1] = H * F(prevX + 0.5 * H, prevZ + 0.5 * l[1]);

        k[3] = H * (prevZ + l[2]);
        l[3] = H * F(prevX + H, prevZ + l[2]);

        logFile << "k1 = " << k[0] << ", "
                << "k2 = " << k[1] << ", "
                << "k3 = " << k[2] << ", "
                << "k4 = " << k[3] << "\n";

        logFile << "l1 = " << l[0] << ", "
                << "l2 = " << l[1] << ", "
                << "l3 = " << l[2] << ", "
                << "l4 = " << l[3] << "\n\n";


        double deltaY = (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
        double deltaZ = (l[0] + 2 * l[1] + 2 * l[2] + l[3]) / 6;

        double y = prevY + deltaY;
        double z = prevZ + deltaZ;
        double exactY = ExactF(prevX);
        double eps = fabs(exactY - prevY);

        logFile << "x = " << x
                << ", y = "<< prevY
                << ", z = "<< prevZ
                << ", deltaY = "<< deltaY
                << ", deltaZ = "<< deltaZ
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n\n";

        ys.push_back(y);
        zs.push_back(z);

        ++step;

    }

}

int main() {
    ofstream logFile("logFile");

    logFile << "TEST\n";

    EulerMethod(logFile);
    RungeKuttaMethods(logFile);

    logFile.close();
    return 0;
}