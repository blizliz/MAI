#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double F(double x) {
    return log(x + 2) - x * x;
}

double Phi1(double x) {
    return sqrt(log(x + 2));
}
double Phi2(double x) {

    return exp(x * x) - 2;
}

double DerivativePhi1(double x) {
    return 0.5 / ((x + 2) * sqrt(log(x + 2)));
}

double DerivativePhi2(double x) {
    return 2 * x * exp(x * x);
}

double CheckCondition(double x, double nextX, double q) {
    return q / (1 - q) * fabs(nextX - x);
}

void IterativeMethod(double eps, ofstream &logFile) {
    logFile << "ITERATIVE METHOD\n";

    double a = 0.5, b = 2.0;
    logFile << "x in [" << a << ", " << b << "]\n\n";

    logFile << "Try x = sqrt(ln(x + 2))\n\n";
    double q = max(fabs(DerivativePhi1(a)), fabs(DerivativePhi1(b)));
    if (q >= 1) {
        logFile << "q = " << q << " >= 1\n\n";
        return;
    } else {
        logFile << "q = " << q << " < 1\n\n";
    }

    int32_t itNum = 0;
    double x = (a + b) / 2.0;
    double nextX;
    double endCond;
    do {
        logFile << "_____________________Iteration #" << itNum << ":\n";
        logFile << "x" << itNum << " = " << x << "\n";
        nextX = Phi1(x);
        endCond = CheckCondition(x, nextX, q);
        x = nextX;
        ++itNum;
    } while(endCond > eps);

    logFile << "\nx = " << x << "\n\n";

    logFile << "Check:\n";
    logFile << "f(x*) = " << F(x) << "\n\n";

    logFile << "Try x = e^(x^2) - 2\n\n";

    q = max(fabs(DerivativePhi2(a)), fabs(DerivativePhi2(b)));
    if (q >= 1) {
        logFile << "q = " << q << " >= 1\n\n";
        return;
    } else {
        logFile << "q = " << q << " < 1\n\n";
    }

    itNum = 0;
    x = (a + b) / 2.0;
    nextX;
    endCond;
    do {
        logFile << "_____________________Iteration #" << itNum << ":\n";
        logFile << "x" << itNum << " = " << x << "\n";
        nextX = Phi2(x);
        double endCond = CheckCondition(x, nextX, q);
        x = nextX;
        ++itNum;
    } while(endCond > eps);

    logFile << "\nx = " << x << "\n\n";

    logFile << "Check:\n";
    logFile << "f(x*) = " << F(x) << "\n\n";
}


double DerivativeF(double x) {
    return 1 / (x + 2) - 2 * x;
}

double SecondDerivativeF(double x) {
    return -1 / ((x + 2) * (x + 2)) - 2;
}

void NewtonsMethod(double eps, ofstream &logFile) {
    logFile << "NEWTON'S METHOD\n";
    double x = 2.0;

    if (F(x) * SecondDerivativeF(x) > 0) {
        logFile << "f * f'' = " << F(x) * SecondDerivativeF(x) << " > 0\n";
    } else {
        logFile << "f * f'' = " << F(x) * SecondDerivativeF(x) << " <= 0\n";
        return;
    }

    double nextX, endCond;
    int32_t itNum = 0;

    do {
        logFile << "_____________________Iteration #" << itNum << ":\n";
        logFile << "x" << itNum << " = " << x << "\n";
        nextX = x - F(x) / DerivativeF(x);
        endCond = fabs(nextX - x);
        x = nextX;
        ++itNum;
    } while (endCond >= eps);

    logFile << "\nx = " << x << "\n\n";

    logFile << "Check:\n";
    logFile << "f(x*) = " << F(x) << "\n\n";
}

int main() {
    ofstream logFile("logFile");

    logFile << "Equation: ln(x + 2) - x^2 = 0\n\n";

    cout << "Set accuracy: ";
    double eps;
    cin >> eps;
    logFile << "Accuracy = " << eps << "\n\n";

    IterativeMethod(eps, logFile);
    NewtonsMethod(eps, logFile);

    logFile.close();
    return 0;
}