#include <iostream>
#include <cmath>
#include "Print.h"
#include "Triangle_matrix_Algorithm.h"

struct Coefficients{
    vector<double> a, b, c, d;
};

double F(Coefficients coeff, const vector<double> &xs, int32_t i, double x) {
    return coeff.a[i] + coeff.b[i] * (x - xs[i - 1])
         + coeff.c[i] * (x - xs[i - 1]) * (x - xs[i - 1])
         + coeff.d[i] * pow((x - xs[i - 1]), 3);
}

void SplineInterpolation(const vector<double> &xs, const vector<double> &f, const double x, ofstream &logFile) {
    int32_t n = xs.size();

    vector<double> diag1(n - 2), diag2(n - 2), diag3(n - 2), right(n - 2);
    diag1[0] = 0;
    diag2[0] = 2 * (xs[2] - xs[0]);
    diag3[0] = xs[2] - xs[1];
    right[0] = 3 * ((f[2] - f[1]) / (xs[2] - xs[1]) - (f[1] - f[0]) / (xs[1] -  xs[0]));

    for (int32_t i = 1; i < n - 3; ++i) {
        diag1[i] = xs[i + 1] - xs[i];
        diag2[i] = 2 * (xs[i + 2] - xs[i]);
        diag3[i] = xs[i + 2] - xs[i + 1];
        right[i] = 3 * ((f[i + 2] - f[i + 1]) / (xs[i + 2] - xs[i + 1]) - (f[i + 1] - f[i]) / (xs[i + 1] - xs[i]));
    }

    diag1[n - 3] = xs[n - 2] - xs[n - 3];
    diag2[n - 3] = 2 * (xs[n - 1] - xs[n - 3]);
    diag3[n - 3] = 0;
    right[n - 3] = 3 * ((f[n - 1] - f[n - 2]) / (xs[n - 1] - xs[n - 2]) - (f[n - 2] - f[n - 3]) / (xs[n - 2] - xs[n - 3]));

    //solving the equation by triangle matrix algorithm
    vector<double> c = FindUnknowns(diag1, diag2, diag3, right);
    c.insert(c.begin(), 0);
    c.insert(c.begin(), 0);

    vector<double> a(n), b(n), d(n);
    for (int32_t i = 1; i < n; ++i) {
        a[i] = f[i - 1];
    }

    for (int32_t i = 1; i < n - 1; ++i) {
        b[i] = (f[i] - f[i - 1]) / (xs[i] - xs[i - 1]) - (xs[i] - xs[i - 1]) * (c[i + 1] + 2 * c[i]) / 3;
        d[i] = (c[i + 1] - c[i]) / (xs[i] - xs[i - 1]) / 3;
    }
    b[n - 1] = (f[n - 1] - f[n - 2]) / (xs[n - 1] - xs[n - 2]) - (xs[n - 1] - xs[n - 2]) * c[n - 1] * 2 / 3;
    d[n - 1] = -c[n - 1] / (xs[n - 1] - xs[n - 2]) / 3;

    logFile << "a: ";
    PrintVectorToFile(a, logFile);
    logFile << "b: ";
    PrintVectorToFile(b, logFile);
    logFile << "c: ";
    PrintVectorToFile(c, logFile);
    logFile << "d: ";
    PrintVectorToFile(d, logFile);

    ofstream spline("../../splinePlot/spline");
    spline << n << "\n";
    for (double x: xs) {
        spline << x << "\n";
    }
    for (double y: f) {
        spline << y << "\n";
    }

    spline << a.size() << "\n";
    for (double el: a) {
        spline << el << "\n";
    }
    for (double el: b) {
        spline << el << "\n";
    }
    for (double el: c) {
        spline << el << "\n";
    }
    for (double el: d) {
        spline << el << "\n";
    }

    Coefficients coeff;
    coeff.a = a;
    coeff.b = b;
    coeff.c = c;
    coeff.d = d;

    if (x < xs[0] || x > xs[n - 1]) {
        logFile << "Point out of range";
        return;
    }
    int32_t seg;  //point segment
    for (int32_t i = 0; i < xs.size() - 1; ++i) {
        if (x >= xs[i] && x <= xs[i + 1]) {
            seg = i + 1;
            break;
        }
    }

    double y = F(coeff, xs, seg, x);
    logFile << "f(" << x << ") = " << y << "\n";

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "More arguments expected";
        return 0;
    }

    if (string(argv[1]) == "--help") {
        cout << "Expected file name where:\n";
        cout << "1 line: n(point number)\n";
        cout << "2 line: points\n";
        cout << "3 line: X*\n";
        return 0;
    }

    ifstream input(argv[1]);
    int32_t n;
    input >> n;

    vector<double> xs(n), f(n);
    for (int32_t i = 0; i < n; ++i) {
        input >> xs[i];
    }
    for (int i = 0; i < n; ++i) {
        input >> f[i];
    }
    double x;
    input >> x;
    input.close();

    ofstream logFile("logFile");
    logFile << "xs: ";
    PrintVectorToFile(xs, logFile);
    logFile << "f(x): ";
    PrintVectorToFile(f, logFile);

    SplineInterpolation(xs, f, x, logFile);

    logFile.close();
    return 0;
}