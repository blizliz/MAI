#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "Print.h"

using namespace std;

double F(double x) {
    return cos(x);
}

vector<double> CalcY(const vector<double> &xs) {
    vector<double> ys;
    for (int32_t i = 0; i < xs.size(); ++i) {
        ys.push_back(F(xs[i]));
    }
    return ys;
}

vector<double> CalcW(const vector<double> &xs) {
    vector<double> ws;
    for (int32_t i = 0; i < xs.size(); ++i) {
        double w = 1;
        for (int32_t j = 0; j < xs.size(); ++j) {
            if(i != j) {
                w *= (xs[i] - xs[j]);
            }
        }
        ws.push_back(w);
    }
    return ws;
}

vector<double> ReadPoints(ifstream &fin) {
    vector<double> points;
    int32_t n;
    double el;
    fin >> n;
    for (int32_t i = 0; i < n; ++i) {
        fin >> el;
        points.push_back(el * M_PI);
    }
    return points;
}

double LagrangePolynomial(const vector<double> &xs, const vector<double> &ys, const vector<double> &ws, double x) {
    double res = 0;
    for (int32_t i = 0; i < xs.size(); ++i) {
        double tmp = ys[i] / ws[i];
        for (int32_t j = 0; j < xs.size(); ++j) {
            if (i != j) {
                tmp *= (x - xs[j]);
            }
        }
        res += tmp;
    }

    return res;
}

void LagrangeInterpolation(vector<double> &xs, double x, ofstream &logFile) {
    logFile << "LAGRANGE INTERPOLATION:\n";

    vector<double> ys = CalcY(xs);
    logFile << "ys: ";
    PrintVectorToFile(ys, logFile);

    vector<double> ws = CalcW(xs);
    logFile << "ws: ";
    PrintVectorToFile(ws, logFile);

    double l = LagrangePolynomial(xs, ys, ws, x);
    double y = F(x);

    logFile << "L(" << x << ") = " << l << ",\n";
    logFile << "y(" << x << ") = " << y << "\n\n";
    logFile << "Absolute interpolation error = " << fabs(l - y) << "\n\n";
}

double NewtonPolynomial (const vector<double> &xs, const vector<vector<double>> &f, double x) {
    double res = 0;
    for (int32_t i = 0; i < xs.size(); ++i) {
        double tmp = f[0][i];
        for (int32_t j = 0; j < i; ++j) {
            tmp *= (x - xs[j]);
        }
        res += tmp;
    }

    return  res;
}

void NewtonInterpoltion(vector<double> &xs, double x, ofstream &logFile) {
    logFile << "NEWTON INTERPOLATION:\n";

    int32_t n = xs.size();
    vector<vector<double>> f(n, vector<double>(n));

    for (int32_t i = 0; i < n; ++i) {
        f[i][i] = F(xs[i]);
        logFile << "f(x" << i << ") = " << f[i][i] << "\n";
    }


    for (int32_t i = 1; i < n; ++i) {
        for (int32_t j = 0; j < n - i; ++j) {
            f[j][j + i] = (f[j][j + i - 1] - f[j + 1][j + i]) / (xs[j] - xs[j + i]);

            //log
            logFile << "f(";
            for (int32_t k = j; k < j + i; ++k) {
                logFile << "x" << k << ", ";
            }
            logFile << "x" << j + i << ") = " << f[j][j + i] << "\n";
        }
    }

    double p = NewtonPolynomial(xs, f, x);
    double y = F(x);

    logFile << "\nP(" << x << ") = " << p << ",\n";
    logFile << "y(" << x << ") = " << y << "\n\n";
    logFile << "Absolute interpolation error = " << fabs(p - y) << "\n\n";
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

    ifstream pointsFile(argv[1]);
    vector<double> xs = ReadPoints(pointsFile);
    double x;
    pointsFile >> x;
    x *= M_PI;
    pointsFile.close();

    ofstream logFile("logFile");

    logFile << "y = cos(x)\n";
    logFile << "xs: ";
    PrintVectorToFile(xs, logFile);
    logFile << "X* = " << x << "\n\n";

    LagrangeInterpolation(xs, x, logFile);
    NewtonInterpoltion(xs, x, logFile);

    logFile.close();

    return 0;
}
