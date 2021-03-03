#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "RungeKuttaMethod.h"
#include "Print.h"
#include "Triangle_matrix_Algorithm.h"

using namespace std;

double FROM = 1;
double TO = 2;
double Y_START = exp(-1);
double Y_END = 0.5 * exp(-2);
double H = 0.05;

double F(double x, double y, double z) {
    return y - 2 * z / x;
}

double ExactF(double x) {
    return exp(-x) / x;
}

void ShootingMethod(ofstream &logFile) {
    logFile << "\nSHOOTING METHOD:\n";
    double eps = 0.0001;

    int32_t step = 0;
    double n0 = 1.0, n1 = 0.8;
    double y = RungeKuttaMethods(FROM, TO, H, Y_START, n0, F).back();
    double phi0 = y - Y_END;

    logFile << step << ": "
            << "n = " << n0
            << ", y(" << TO << ", " << Y_START << ", " << n0 << ") = " << y
            << ", |Phi(n)| = " << fabs(phi0)
            << "\n";

    ++step;
    y = RungeKuttaMethods(FROM, TO, H, Y_START, n1, F).back();
    double_t phi1 = y - Y_END;

    logFile << step << ": "
            << "n = " << n1
            << ", y(" << TO << ", " << Y_START << ", " << n1 << ") = " << y
            << ", |Phi(n)| = " << fabs(phi1)
            << "\n";

    double n, phi;
    do {
        n = n1 - (n1 - n0) * phi1 / (phi1 - phi0);
        y = RungeKuttaMethods(FROM, TO, H, Y_START, n, F).back();
        phi = y - Y_END;

        logFile << ++step << ": "
                << "n = " << n
                << ", y(" << TO << ", " << Y_START << ", " << n << ") = " << y
                << ", |Phi(n)| = " << fabs(phi)
                << "\n";

        n0 = n1;
        n1 = n;
        phi0 = phi1;
        phi1 = phi;
    } while (fabs(phi) > eps);

    vector<double> xs;
    for (double x = FROM; x <= TO; x += H) {
        xs.push_back(x);
    }

    vector<double> ys = RungeKuttaMethods(FROM, TO, H, Y_START, n, F);

    logFile << "\n";
    for (int i = 0; i < xs.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs[i]
                     << ", y" << i << " = " << ys[i] << "\n";
    }

    ofstream data("../../plot/shooting_method");
    data << xs.size() << "\n";
    for (double x: xs) {
        data << x << "\n";
    }
    for (double y: ys) {
        data << y << "\n";
    }

    data.close();

    vector<double> err1;
    for (int i = 0; i < xs.size(); ++i) {
        err1.push_back(fabs(ExactF(xs[i]) - ys[i]));
    }

    vector<double> err2;
    for (int i = 0; i < ys.size() - 1; ++i) {
        double e = fabs(ys[i] - ys[i + 1]) / (pow(2, 4) - 1);
        err2.push_back(e);
    }

    logFile << "\nErrors:\n"
            << "1) Comparison with exact solution:\n";
    PrintVectorToFile(err1, logFile);
    logFile << "2) Runge-Romberg method:\n";
    PrintVectorToFile(err2, logFile);
}

double q(double x) {
    return -1;
}

double p(double x) {
    return 2 / x;
}

void FiniteDifferenceMethod(ofstream &logFile) {
    logFile << "\nFINITE DIFFERENCE METHOD:\n";
    vector<double> xs;
    for (double x = FROM; x <= TO; x += H) {
        xs.push_back(x);
    }

    int32_t n = xs.size();
    vector<double> ys(n);
    ys[0] = Y_START;
    ys[n - 1] = Y_END;

    vector<double> a, b, c, d;
    a.push_back(0);
    b.push_back(-2 + H * H * q(xs[1]));
    c.push_back(1 + p(xs[1]) * H / 2);
    d.push_back(-(1 - p(xs[1]) * H / 2) * Y_START);

    for (int i = 2; i <= n - 2; ++i) {
        a.push_back(1 - p(xs[i]) * H / 2);
        b.push_back(-2 + H * H * q(xs[i]));
        c.push_back(1 + p(xs[i]) * H / 2);
        d.push_back(0);
    }

    a.push_back(1 - p(xs[n - 1]) * H / 2);
    b.push_back(-2 + H * H * q(xs[n - 1]));
    c.push_back(0);
    d.push_back(-(1 + p(xs[n - 1]) * H / 2) * Y_END);


    vector<double> ysMid = FindUnknowns(a, b, c, d);
    for (int i = 1; i < n - 1; ++i) {
        ys[i] = ysMid[i - 1];
    }

    for (int i = 0; i < xs.size(); ++i) {
        logFile << i << ": x" << i << " = " << xs[i]
                << ", y" << i << " = " << ys[i] << "\n";
    }

    ofstream data("../../plot/finite_diff_method");
    data << xs.size() << "\n";
    for (double x: xs) {
        data << x << "\n";
    }
    for (double y: ys) {
        data << y << "\n";
    }

    vector<double> err1;
    for (int i = 0; i < xs.size(); ++i) {
        err1.push_back(fabs(ExactF(xs[i]) - ys[i]));
    }

    vector<double> err2;
    for (int i = 0; i < ys.size() - 1; ++i) {
        double e = fabs(ys[i] - ys[i + 1]) / (pow(2, 4) - 1);
        err2.push_back(e);
    }

    logFile << "\nErrors:\n"
            << "1) Comparison with exact solution:\n";
    PrintVectorToFile(err1, logFile);
    logFile << "2) Runge-Romberg method:\n";
    PrintVectorToFile(err2, logFile);
}

int main() {
    ofstream logFile("logFile");

    ShootingMethod(logFile);
    FiniteDifferenceMethod(logFile);

    logFile.close();
    return 0;
}