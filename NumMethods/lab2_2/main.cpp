#include <iostream>
#include <fstream>
#include <cmath>
#include "Matrix.h"
#include "Print.h"
#include "VectorOperations.h"
#include "LUP_Algorithm.h"

using namespace std;

const int32_t N = 2; //unknowns number

double F1(const vector<double> &x) {
    return (x[0] * x[0] + 9) * x[1] - 27;
}

double F2(const vector<double> &x) {
    return (x[0] - 1.5) * (x[0] - 1.5) + (x[1] - 1.5) * (x[1] - 1.5) - 9;
}

double Phi2(const vector<double> &x) {
    return 27.0 / (x[0] * x[0] + 9.0);
}

double Phi1(const vector<double> &x) {
    return sqrt(9.0 - (x[1] - 1.5) * (x[1] - 1.5)) + 1.5;
}

double CheckJacobiMatrix2(const vector<double> &x) {
    return fabs(-54.0 * x[0] / ((x[0] * x[0] + 9.0) * (x[0] * x[0] + 9.0)));
}

double CheckJacobiMatrix1(const vector<double> &x) {
    return fabs((-x[1] + 1.5) / sqrt(9.0 - (x[1] - 1.5) * (x[1] - 1.5)));
}

double VectorNorm(vector<double> &v) {
    double max = 0;
    for (double el: v) {
        if (fabs(el) > max) {
            max = fabs(el);
        }
    }
    return max;
}

double CheckCond(vector<double> &x, vector<double> &nextX, double q) {
    vector<double> diffX = {nextX[0] - x[0],
                            nextX[1] - x[1]};

    return q / (1 - q) * VectorNorm(diffX);

}

void IterativeMethod(double eps, ofstream &logFile) {
    logFile << "ITERATIVE METHOD\n";

    double a1 = 4.0, b1 = 4.5;
    double a2 = 0.1, b2 = 0.5;


    vector<double> x(N);
    x[0] = (a1 + b1) / 2;
    x[1] = (a2 + b2) / 2;

    double q = max(CheckJacobiMatrix1(x), CheckJacobiMatrix2(x));
    if (q >= 1) {
        logFile << "q = " << q << " >= 1\n\n";
        return;
    } else {
        logFile << "q = " << q << " < 1\n\n";
    }

    double endCond;
    int32_t itNum = 0;
    vector<double> nextX(N);
    do {
        logFile << "_____________________Iteration #" << itNum << ":\n";
        logFile << "x" << itNum << ": ";
        PrintVectorToFile(x, logFile);

        nextX[0] = Phi1(x);
        nextX[1] = Phi2(x);

        endCond = CheckCond(x, nextX, q);

        x = nextX;
        ++itNum;
    } while(endCond > eps);

    logFile << "x*: ";
    PrintVectorToFile(x, logFile);
}

double DF1dx1(const vector<double> &x) {
    return 2 * x[0] * x[1];
}

double DF1dx2(const vector<double> &x) {
    return x[0] * x[0] + 9;
}

double DF2dx1(const vector<double> &x) {
    return 2 * (x[0] - 1.5);
}

double DF2dx2(const vector<double> &x) {
    return 2 * (x[1] - 1.5);
}

void NewtonsMethod(double eps, ofstream &logFile) {
    logFile << "NEWTON'S METHOD\n";

    vector<double> x(N);
    x[0] = 4.25;
    x[1] = 0.3;

    double endCond;
    vector<double> nextX(N);
    int32_t itNum = 0;
    do {
        logFile << "_____________________Iteration #" << itNum << ":\n";
        logFile << "x" << itNum << ": ";
        PrintVectorToFile(x, logFile);
        //find b vector in Ax = b equation
        vector<double> b(N);
        b[0] = -F1(x);
        b[1] = -F2(x);

        //find A matrix
        Matrix A(N);
        A.change(0, 0, DF1dx1(x));
        A.change(0, 1, DF1dx2(x));
        A.change(1, 0, DF2dx1(x));
        A.change(1, 1, DF2dx2(x));

        vector<double> deltaX = FindUnknowns(A, b);

        nextX = Add(x, deltaX);

        vector<double> diffX = Subtract(nextX, x);
        endCond = VectorNorm(diffX);

        x = nextX;
        ++itNum;
    } while (endCond > eps);

    logFile << "x*: ";
    PrintVectorToFile(x, logFile);
}

int main() {
    ofstream logFile("logFile");

    cout << "Set accuracy: ";
    double eps;
    cin >> eps;
    logFile << "Accuracy = " << eps << "\n\n";

    IterativeMethod(eps, logFile);
    NewtonsMethod(eps, logFile);

    logFile.close();
    return 0;
}