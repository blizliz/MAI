#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "Print.h"

using namespace std;

double frac(const vector<double> &xs, const vector<double> &ys, int32_t i) {
    return (ys[i] - ys[i - 1]) / (xs[i] - xs[i - 1]);
}

void FirstDerivative(const vector<double> &xs, const vector<double> &ys, double x, ofstream &logFile) {
    logFile << "First derivative:\n\n";
    int32_t n = xs.size();

    int32_t seg;
    if (x < xs[0] || x > xs[n - 1]) {
        logFile << "Point out of range";
        return;
    }
    for (int32_t i = 0; i < n - 1; ++i) {
        if (x >= xs[i] && x <= xs[i + 1]) {
            seg = i + 1;
            break;
        }
    }

    double leftDeriv1 = frac(xs, ys, seg);
    double rightDeriv1 = frac(xs, ys, seg + 1);

    logFile << "First order of accuracy:\n";
    logFile << "Left-side y'(" << x << ") = " << leftDeriv1 << "\n";
    logFile << "Right-side y'(" << x << ") = " << rightDeriv1 << "\n";
    logFile << "y'(" << x << ") = " << (leftDeriv1 + rightDeriv1) / 2 << "\n\n";

    double deriv2 = frac(xs, ys, seg)
                  + (frac(xs, ys, seg + 1) - frac(xs, ys, seg)) / (xs[seg + 1] - xs[seg - 1])
                  * (2 * x - xs[seg - 1] - xs[seg]);

    logFile << "Second order of accuracy:\n";
    logFile << "y'(" << x << ") = " << deriv2 << "\n";
}

void SecondDerivative(const vector<double> &xs, const vector<double> &ys, double x, ofstream &logFile) {
    logFile << "\nSecond derivative:\n\n";
    int32_t n = xs.size();

    int32_t seg;
    if (x < xs[0] || x > xs[n - 1]) {
        logFile << "Point out of range";
        return;
    }
    for (int32_t i = 0; i < n - 1; ++i) {
        if (x >= xs[i] && x <= xs[i + 1]) {
            seg = i + 1;
            break;
        }
    }

    double secondDeriv = 2 * (frac(xs, ys, seg + 1) - frac(xs, ys, seg)) / (xs[seg + 1] - xs[seg - 1]);
    logFile << "y''(" << x << ") = " << secondDeriv << "\n";
}

double F(double x) {
    return x * x * x;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "More arguments expected";
        return 0;
    }

    if (string(argv[1]) == "--help") {
        cout << "Expected file name where:\n";
        cout << "1 line: n(point number)\n";
        cout << "2 line: xs\n";
        cout << "2 line: ys\n";
        cout << "4 line: X*\n";
        return 0;
    }

    ifstream input(argv[1]);
    int32_t n;
    input >> n;

    vector<double> xs(n), ys(n);
    for (int32_t i = 0; i < n; ++i) {
        input >> xs[i];
    }
    for (int i = 0; i < n; ++i) {
        input >> ys[i];
    }
    double x;
    input >> x;
    input.close();

    ofstream logFile("logFile");

    logFile << "xs: ";
    PrintVectorToFile(xs, logFile);
    logFile << "ys: ";
    PrintVectorToFile(ys, logFile);

    vector<double> myYs;

    for (int i = 0; i < xs.size(); ++i) {
        myYs.push_back(F(xs[i]));
    }

//    FirstDerivative(xs, ys, x, logFile);
    FirstDerivative(xs, myYs, x, logFile);


//    SecondDerivative(xs,ys, x, logFile);
    SecondDerivative(xs, myYs, x, logFile);

    logFile.close();
    return 0;
}