#include <iostream>
#include <cmath>
#include <vector>
#include "Print.h"
#include "LUP_Algorithm.h"
#include "Matrix.h"

using namespace std;

vector<double> F(const vector<double> &a, const vector<double> &xs) {
    vector<double> f(xs.size(), 0);
    for (int i = 0; i < xs.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            f[i] += a[j] * pow(xs[i], j);
        }
    }
    return f;
}

double SumOfPow(const vector<double> &xs, int32_t p) {
    double sum = 0;
    for (int32_t i = 0; i < xs.size(); ++i) {
        sum += pow(xs[i], p);
    }
    return sum;
}

double DotProduct(const vector<double> &xs, const vector<double> &ys, int32_t p) {
    double sum = 0;
    for (int32_t i = 0; i < xs.size(); ++i) {
        sum += pow(xs[i], p) * ys[i];
    }
    return sum;
}

vector<double> ApproxPolynomial(const vector<double> &xs, const vector<double> &ys, int32_t degree, ofstream &logFile) {
    logFile << "\n\nApproximating " << degree << "-degree polynomial:\n\n";
    int32_t n = xs.size();

    Matrix A(degree + 1);
    for (int32_t i = 0; i < degree + 1; ++i) {
        for (int32_t j = 0; j < degree + 1; ++j) {
            if (i == 0 && j == 0) {
                A.change(0, 0, n);
            } else {
                A.change(i, j, SumOfPow(xs, i + j));
            }
        }
    }
    logFile << "Matrix A:\n";
    PrintMatrixToFile(A, logFile);

    vector<double> b(degree + 1);
    for (int32_t i = 0; i < degree + 1; ++i) {
        b[i] = DotProduct(xs, ys, i);
    }
    logFile << "Vector b:\n";
    PrintVectorToFile(b, logFile);

    vector<double> a = FindUnknowns(A, b);
    for (int32_t i = 0; i < degree + 1; ++i) {
        logFile << "a" << i << " = " << a[i] << "\n";
    }

    vector<double> f = F(a, xs);
    logFile << "f(x): ";
    PrintVectorToFile(f, logFile);

    double sumSquareError = 0; //sum of squared errors
    for (int32_t i = 0; i < n; ++i) {
        sumSquareError += (ys[i] - f[i]) * (ys[i] - f[i]);
    }

    logFile << "Sum of square errors = " << sumSquareError;
    return a;
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

    vector<double> xs(n), ys(n);
    for (int32_t i = 0; i < n; ++i) {
        input >> xs[i];
    }
    for (int i = 0; i < n; ++i) {
        input >> ys[i];
    }
    input.close();

    ofstream logFile("logFile");

    logFile << "xs: ";
    PrintVectorToFile(xs, logFile);
    logFile << "ys: ";
    PrintVectorToFile(ys, logFile);

    ofstream coeff("../../plot/coeff");
    coeff << xs.size() << "\n";
    for (double x: xs) {
        coeff << x << "\n";
    }
    for (double y: ys) {
        coeff << y << "\n";
    }

    vector<double> coeff1 = ApproxPolynomial(xs, ys, 1, logFile);
    vector<double> coeff2 = ApproxPolynomial(xs, ys, 2, logFile);

    for (auto it = coeff1.begin(); it != coeff1.end(); ++it) {
        coeff << *it << "\n";
    }
    for (auto it = coeff2.begin(); it != coeff2.end(); ++it) {
        coeff << *it << "\n";
    }
    coeff.close();

    logFile.close();
    return 0;
}