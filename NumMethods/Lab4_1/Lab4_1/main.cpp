#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Print.h"

using namespace std;

double FROM = 0;
double TO = 1;
double H1 = 0.1;
double H2 = 0.2;
double X0 = 0;
double Y0 = 1;
double Z0 = 0;

double F(double x, double y) {
    return -y + 2 * cos(x);
}

double ExactF(double x) {
    return x * sin(x) + cos(x);
}

void EulerMethod(ofstream &logFile) {
    logFile << "\nEULER METOD with step = " << H1 << "\n";
    vector<double> xs1, ys1, zs1;

    xs1.push_back(X0);
    ys1.push_back(Y0);
    zs1.push_back(Z0);

    logFile << 0 << ": "

            << "x = " << X0
            << ", y = "<< Y0
            << ", z = "<< Z0
            << ", y(exact) = " << ExactF(X0)
            << ", eps = " << fabs(ExactF(X0) - Y0) << "\n";

    int32_t step = 1;

    for (double x = FROM + H1; x < TO; x += H1) {
        double prevX = xs1.back();
        double prevY = ys1.back();
        double prevZ = zs1.back();

        double y = prevY + H1 * prevZ;
        double z = prevZ + H1 * F(prevX, prevY);

        xs1.push_back(x);
        ys1.push_back(y);
        zs1.push_back(z);

        double exactY = ExactF(x);
        double eps = fabs(exactY - prevY);

        logFile << step << ": "
                << "x = " << x
                << ", y = "<< y
                << ", z = "<< z
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n";

        ++step;
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs1.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs1[i] << ", y" << i << " = " << ys1[i] << "\n\n";
    }

    ofstream data("../../plot/euler_method1");
    data << xs1.size() << "\n";
    for (double x: xs1) {
        data << x << "\n";
    }
    for (double y: ys1) {
        data << y << "\n";
    }
    data.close();


    logFile << "\nEULER METOD with step = " << H2 << "\n";
    vector<double> xs2, ys2, zs2;

    xs2.push_back(X0);
    ys2.push_back(Y0);
    zs2.push_back(Z0);

    logFile << 0 << ": "
            << "x = " << X0
            << ", y = "<< Y0
            << ", z = "<< Z0
            << ", y(exact) = " << ExactF(X0)
            << ", eps = " << fabs(ExactF(X0) - Y0) << "\n";

    step = 1;

    for (double x = FROM + H2; x <= TO; x += H2) {
        double prevX = xs2.back();
        double prevY = ys2.back();
        double prevZ = zs2.back();

        double y = prevY + H2 * prevZ;
        double z = prevZ + H2 * F(prevX, prevY);

        xs2.push_back(x);
        ys2.push_back(y);
        zs2.push_back(z);

        double exactY = ExactF(x);
        double eps = fabs(exactY - prevY);

        logFile << step << ": "
                << "x = " << x
                << ", y = "<< y
                << ", z = "<< z
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n";

        ++step;
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs2.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs2[i] << ", y" << i << " = " << ys2[i] << "\n\n";
    }

    ofstream data1("../../plot/euler_method2");
    data1 << xs2.size() << "\n";
    for (double x: xs2) {
        data1 << x << "\n";
    }
    for (double y: ys2) {
        data1 << y << "\n";
    }
    data1.close();

    //error estimation using the Runge-Romberg method
    vector<double> err;
    double k = H2 / H1;
    for (int i = 0; i < ys2.size() - 1; ++i) {
        double e = fabs(ys1[i] - ys2[i]) / (pow(k, 1) - 1);
        err.push_back(e);
    }

    logFile << "Error estimation using the Runge-Romberg method:\n";
    PrintVectorToFile(err, logFile);

}

void RungeKuttaMethods(ofstream &logFile) {
    logFile << "\nRUNGE-KUTTA METOD with h = " << H1 << ":\n";
    vector<double> xs1, ys1, zs1;

    xs1.push_back(X0);
    ys1.push_back(Y0);
    zs1.push_back(Z0);

    vector<double> k(4), l(4);

    int32_t step = 0;

    for (double x = FROM; x < TO - H1; x += H1) {
        logFile << "_______________step #" << step << ":\n";
        double prevX = xs1.back();
        double prevY = ys1.back();
        double prevZ = zs1.back();

        //fill K and L vectors
        k[0] = H1 * prevZ;
        l[0] = H1 * F(prevX, prevY);

        k[1] = H1 * (prevZ + 0.5 * l[0]);
        l[1] = H1 * F(prevX + 0.5 * H1, prevY + 0.5 * k[0]);

        k[2] = H1 * (prevZ + 0.5 * l[1]);
        l[2] = H1 * F(prevX + 0.5 * H1, prevY + 0.5 * k[1]);

        k[3] = H1 * (prevZ + l[2]);
        l[3] = H1 * F(prevX + H1, prevY + k[2]);

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
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", deltaY = " << deltaY
                << ", deltaZ = " << deltaZ
                << ", y(exact) = " << exactY
                << ", eps = " << eps
                << "\n\n";

        xs1.push_back(x + H1);
        ys1.push_back(y);
        zs1.push_back(z);

        ++step;
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs1.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs1[i] << ", y" << i << " = " << ys1[i] << "\n\n";
    }

    ofstream data("../../plot/rk_method1");
    data << xs1.size() << "\n";
    for (double x: xs1) {
        data << x << "\n";
    }
    for (double y: ys1) {
        data << y << "\n";
    }
    data.close();



    logFile << "\nRUNGE-KUTTA METOD with h = " << H2 << ":\n";
    vector<double> xs2, ys2, zs2;

    xs2.push_back(X0);
    ys2.push_back(Y0);
    zs2.push_back(Z0);

    vector<double> k1(4), l1(4);

    step = 0;

    for (double x = FROM; x < TO; x += H2) {
        logFile << "_______________step #" << step << ":\n";
        double prevX = xs2.back();
        double prevY = ys2.back();
        double prevZ = zs2.back();

        //fill K and L vectors
        k1[0] = H2 * prevZ;
        l1[0] = H2 * F(prevX, prevY);

        k1[1] = H2 * (prevZ + 0.5 * l1[0]);
        l1[1] = H2 * F(prevX + 0.5 * H2, prevY + 0.5 * k1[0]);

        k1[2] = H2 * (prevZ + 0.5 * l1[1]);
        l1[2] = H2 * F(prevX + 0.5 * H2, prevY + 0.5 * k1[1]);

        k1[3] = H2 * (prevZ + l1[2]);
        l1[3] = H2 * F(prevX + H2, prevY + k1[2]);

        logFile << "k1 = " << k1[0] << ", "
                << "k2 = " << k1[1] << ", "
                << "k3 = " << k1[2] << ", "
                << "k4 = " << k1[3] << "\n";

        logFile << "l1 = " << l1[0] << ", "
                << "l2 = " << l1[1] << ", "
                << "l3 = " << l1[2] << ", "
                << "l4 = " << l1[3] << "\n\n";


        double deltaY = (k1[0] + 2 * k1[1] + 2 * k1[2] + k1[3]) / 6;
        double deltaZ = (l1[0] + 2 * l1[1] + 2 * l1[2] + l1[3]) / 6;

        double y = prevY + deltaY;
        double z = prevZ + deltaZ;
        double exactY = ExactF(prevX);
        double eps = fabs(exactY - prevY);

        logFile << "x = " << x
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", deltaY = " << deltaY
                << ", deltaZ = " << deltaZ
                << ", y(exact) = " << exactY
                << ", eps = " << eps
                << "\n\n";

        xs2.push_back(x + H2);
        ys2.push_back(y);
        zs2.push_back(z);

        ++step;
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs2.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs2[i] << ", y" << i << " = " << ys2[i] << "\n\n";
    }

    ofstream data1("../../plot/rk_method2");
    data1 << xs2.size() << "\n";
    for (double x: xs2) {
        data1 << x << "\n";
    }
    for (double y: ys2) {
        data1 << y << "\n";
    }
    data1.close();

    //error estimation using the Runge-Romberg method
    vector<double> err;
    double m = H2 / H1;
    for (int i = 0; i < ys2.size() - 1; ++i) {
        double e = fabs(ys1[i] - ys2[i]) / (pow(m, 1) - 1);
        err.push_back(e);
    }

    logFile << "Error estimation using the Runge-Romberg method:\n";
    PrintVectorToFile(err, logFile);
}

void AdamsMethod(ofstream &logFile) {
    logFile << "\nADAMS METOD with h = " << H1 << ":\n";
    vector<double> xs1, ys1, zs1;

    ys1.push_back(Y0);
    zs1.push_back(Z0);

    //finding solution in first 4 nodes by Runge-Kutta method
    vector<double> k(4), l(4);
    int32_t step = 0;

    for (double x = FROM; x < TO - H1; x += H1) {
        logFile << "_______________step #" << step << ":\n";
        double prevX = x;
        double prevY = ys1.back();
        double prevZ = zs1.back();

        //fill K and L vectors
        k[0] = H1 * prevZ;
        l[0] = H1 * F(prevX, prevY);

        k[1] = H1 * (prevZ + 0.5 * l[0]);
        l[1] = H1 * F(prevX + 0.5 * H1, prevY + 0.5 * k[0]);

        k[2] = H1 * (prevZ + 0.5 * l[1]);
        l[2] = l[1] = H1 * F(prevX + 0.5 * H1, prevY + 0.5 * k[1]);

        k[3] = H1 * (prevZ + l[2]);
        l[3] = H1 * F(prevX + H1, prevY + k[2]);


        double deltaY = (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
        double deltaZ = (l[0] + 2 * l[1] + 2 * l[2] + l[3]) / 6;

        double y = prevY + deltaY;
        double z = prevZ + deltaZ;
        double exactY = ExactF(prevX);
        double eps = fabs(exactY - prevY);

        logFile << "x = " << x
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", deltaY = " << deltaY
                << ", deltaZ = " << deltaZ
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n\n";

        xs1.push_back(x);
        ys1.push_back(y);
        zs1.push_back(z);

        if (step == 3) {
            break;
        }
        ++step;
    }

    for (double x = xs1.back() + H1, i = 3; x < TO; x += H1, ++i) {
        double prevY = ys1.back();
        double prevZ = zs1.back();

        double y = prevY + H1 * (55 * zs1[i] - 59 * zs1[i - 1] + 37 * zs1[i - 2] - 9 * zs1[i - 3]) / 24;
        double z = prevZ + H1 * (55 * F(xs1[i], ys1[i]) - 59 * F(xs1[i - 1], ys1[i - 1]) + 37 * F(xs1[i - 2], ys1[i - 2]) - 9 * F(xs1[i - 3], ys1[i - 3])) / 24;

        xs1.push_back(x);
        ys1.push_back(y);
        zs1.push_back(z);

        logFile << "x = " << x
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", y(exact) = " << ExactF(x)
                << ", eps = " << fabs(ExactF(x) - prevY) << "\n";
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs1.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs1[i] << ", y" << i << " = " << ys1[i] << "\n\n";
    }

    ofstream data("../../plot/adams_method1");
    data << xs1.size() << "\n";
    for (double x: xs1) {
        data << x << "\n";
    }
    for (double y: ys1) {
        data << y << "\n";
    }
    data.close();


    logFile << "\nADAMS METOD with h = " << H2 << ":\n";
    vector<double> xs2, ys2, zs2;

    ys2.push_back(Y0);
    zs2.push_back(Z0);

    //finding solution in first 4 nodes by Runge-Kutta method
    vector<double> k1(4), l1(4);
    step = 0;

    for (double x = FROM; x < TO - H2; x += H2) {
        logFile << "_______________step #" << step << ":\n";
        double prevX = x;
        double prevY = ys2.back();
        double prevZ = zs2.back();

        //fill K and L vectors
        k1[0] = H2 * prevZ;
        l1[0] = H2 * F(prevX, prevY);

        k1[1] = H2 * (prevZ + 0.5 * l1[0]);
        l1[1] = H2 * F(prevX + 0.5 * H2, prevY + 0.5 * k1[0]);

        k1[2] = H2 * (prevZ + 0.5 * l1[1]);
        l1[2] = l1[1] = H2 * F(prevX + 0.5 * H2, prevY + 0.5 * k1[1]);

        k1[3] = H2 * (prevZ + l1[2]);
        l1[3] = H2 * F(prevX + H2, prevY + k1[2]);


        double deltaY = (k1[0] + 2 * k1[1] + 2 * k1[2] + k1[3]) / 6;
        double deltaZ = (l1[0] + 2 * l1[1] + 2 * l1[2] + l1[3]) / 6;

        double y = prevY + deltaY;
        double z = prevZ + deltaZ;
        double exactY = ExactF(prevX);
        double eps = fabs(exactY - prevY);

        logFile << "x = " << x
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", deltaY = " << deltaY
                << ", deltaZ = " << deltaZ
                << ", y(exact) = " << exactY
                << ", eps = " << eps << "\n\n";

        xs2.push_back(x);
        ys2.push_back(y);
        zs2.push_back(z);

        if (step == 3) {
            break;
        }
        ++step;
    }

    for (double x = xs2.back() + H2, i = 3; x <= TO; x += H2, ++i) {
        double prevY = ys2.back();
        double prevZ = zs2.back();

        double y = prevY + H2 * (55 * zs2[i] - 59 * zs2[i - 1] + 37 * zs2[i - 2] - 9 * zs2[i - 3]) / 24;
        double z = prevZ + H2 * (55 * F(xs2[i], ys2[i]) - 59 * F(xs2[i - 1], ys2[i - 1]) + 37 * F(xs2[i - 2], ys2[i - 2]) - 9 * F(xs2[i - 3], ys2[i - 3])) / 24;

        xs2.push_back(x);
        ys2.push_back(y);
        zs2.push_back(z);

        logFile << "x = " << x
                << ", y = " << prevY
                << ", z = " << prevZ
                << ", y(exact) = " << ExactF(x)
                << ", eps = " << fabs(ExactF(x) - prevY) << "\n";
    }

    logFile << "Solution:\n";
    for (int i = 0; i < xs2.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs2[i] << ", y" << i << " = " << ys2[i] << "\n\n";
    }

    ofstream data1("../../plot/adams_method2");
    data1 << xs2.size() << "\n";
    for (double x: xs2) {
        data1 << x << "\n";
    }
    for (double y: ys2) {
        data1 << y << "\n";
    }
    data1.close();

    //error estimation using the Runge-Romberg method
    vector<double> err;
    double m = H2 / H1;
    for (int i = 0; i < ys2.size() - 1; ++i) {
        double e = fabs(ys1[i] - ys2[i]) / (pow(m, 4) - 1);
        err.push_back(e);
    }

    logFile << "Error estimation using the Runge-Romberg method:\n";
    PrintVectorToFile(err, logFile);
}

int main() {
    ofstream logFile("logFile");

    logFile << "y' = (y + x)^2\n";

    EulerMethod(logFile);
    RungeKuttaMethods(logFile);
    AdamsMethod(logFile);

    logFile.close();
    return 0;
}