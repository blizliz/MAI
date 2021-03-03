#include <iostream>
#include <fstream>
#include <math.h>
#include "Print.h"

using namespace std;

double EXACT_SOLUTION = 0.071;
double H1 = 1.0;
double H2 = 0.5;
double X0 = 0;
double Xk = 4;

double F(double x) {
    return x / ((3 * x + 4) * (3 * x + 4));
}

void RectangleMethod(ofstream &logFile) {
    logFile << "\nRECTANGLE METHOD with step h = " << H1 << ":\n";

    double f1 = 0;
    for (double x = X0; x + H1 <= Xk; x += H1) {
        logFile << "x = " << x + H1 << ", ";
        f1 += H1 * F((x + x + H1) / 2);
        logFile << "f = " << f1 << "\n";
    }

    logFile << "\nF = " << f1 << "\n"
            << "errors:" << fabs(f1 - EXACT_SOLUTION) << "\n\n";

    logFile << "\nRECTANGLE METHOD with step h = " << H2 << ":\n";

    double f2 = 0;
    for (double x = X0; x + H2 <= Xk; x += H2) {
        logFile << "x = " << x + H2 << ", ";
        f2 += H2 * F((x + x + H2) / 2);
        logFile << "f = " << f2 << "\n";
    }

    logFile << "\nF = " << f2 << "\n"
            << "Error = " << fabs(f2 - EXACT_SOLUTION) << "\n";

    double k = H2 / H1;
    logFile << "Runge-Romberg error: " << (f1 - f2) / (pow(k, 2) - 1) << "\n";
}

void TrapezoidalMethod(ofstream &logFile) {
    logFile << "\nTRAPEZOIDAL METHOD with step h = " << H1 << ":\n";

    double f1 = 0;
    for (double x = X0 + H1; x <= Xk; x += H1) {
        logFile << "x = " << x << ", ";
        f1 += 0.5 * H1 * (F(x) + F(x - H1));
        logFile << "f = " << f1 << "\n";
    }

    logFile << "\nF = " << f1 << "\n";
    logFile << "Error = " << fabs(f1 - EXACT_SOLUTION) << "\n";

    logFile << "\nTRAPEZOIDAL METHOD with step h = " << H2 << ":\n";

    double f2 = 0;
    for (double x = X0 + H2; x <= Xk; x += H2) {
        logFile << "x = " << x << ", ";
        f2 += 0.5 * H2 * (F(x) + F(x - H2));
        logFile << "f = " << f2 << "\n";
    }

    logFile << "\nF = " << f2 << "\n";
    logFile << "Error = " << fabs(f2 - EXACT_SOLUTION) << "\n";

    double k = H2 / H1;
    logFile << "Runge-Romberg error: " << (f1 - f2) / (pow(k, 2) - 1) << "\n";
}

void SimpsonMethod(ofstream &logFile) {
    logFile << "\nSIMPSON METHOD with step h = " << H1 << ":\n";

    double f1 = 0;
    for (double x = X0 + H1; x <= Xk; x += 2 * H1) {
        logFile << "x = " << x << ", ";
        f1 += (H1 / 3) * (F(x - H1) + 4 * F(x) + F(x + H1));
        logFile << "f1 = " << f1 << "\n";
    }

    logFile << "\nF = " << f1 << "\n";
    logFile << "Error = " << fabs(f1 - EXACT_SOLUTION) << "\n";

    logFile << "\nSIMPSON METHOD with step h = " << H1 << ":\n";

    double f2 = 0;
    for (double x = X0 + H2; x <= Xk; x += 2 * H2) {
        logFile << "x = " << x << ", ";
        f2 += (H2 / 3) * (F(x - H2) + 4 * F(x) + F(x + H2));
        logFile << "f1 = " << f2 << "\n";
    }

    logFile << "\nF = " << f2 << "\n";
    logFile << "Error = " << fabs(f2 - EXACT_SOLUTION) << "\n";

    double k = H2 / H1;
    logFile << "Runge-Romberg error: " << (f1 - f2) / (pow(k, 4) - 1) << "\n";
}

double RungeRombergRichardsonMethod(double Fh, double Fkh, double k) {
    double F = Fh + (Fh - Fkh) / (k * k - 1);
}

int main(int argc, char* argv[]) {

    ofstream logFile("logFile");
    logFile << "X0 = " << X0 << ", Xk = " << Xk << "\n";
    logFile << "Exact solution = " << EXACT_SOLUTION << "\n";

    RectangleMethod(logFile);
    TrapezoidalMethod(logFile);
    SimpsonMethod(logFile);

    logFile.close();
    return 0;
}