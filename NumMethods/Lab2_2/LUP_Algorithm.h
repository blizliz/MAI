#ifndef LAB2_2_LUP_ALGORITHM_H
#define LAB2_2_LUP_ALGORITHM_H

#include "Matrix.h"
#include <cmath>

void LUP(Matrix &A, Matrix &C, Matrix &P) {
    const int32_t n = A.size();

    C = A;
    P.IdentityMatrix(n);

    for (int32_t i = 0; i < n; ++i) {
        double pilotValue = 0;
        int32_t pilot = -1;
        for (int32_t j = i; j < n; ++j) {
            if (fabs(C.get(j, i)) > pilotValue) {
                pilotValue = fabs(C.get(j, i));
                pilot = j;
            }
        }
        if (pilotValue != 0) {
            P.SwapLines(pilot, i);
            C.SwapLines(pilot, i);
            for (int j = i + 1; j < n; ++j) {
                C.change(j, i, C.get(j, i) / C.get(i, i));
                for (int k = i + 1; k < n; ++k) {
                    double tmp = C.get(j, k) - C.get(j, i) * C.get(i, k);
                    C.change(j, k, tmp);
                }
            }
        }
    }
}

Matrix FindL(Matrix &C) {
    Matrix L(C.size());
    for (int32_t i = 0; i < C.size(); ++i) {
        for (int32_t j = 0; j < C.size(); ++j) {
            if (i == j) {
                L.change(i, i, 1);
            } else if (i > j) {
                L.change(i, j, C.get(i, j));
            }
        }
    }
    return L;
}

Matrix FindU(Matrix &C) {
    Matrix U(C.size());
    for (int32_t i = 0; i < C.size(); ++i) {
        for (int32_t j = 0; j < C.size(); ++j) {
            if (i <= j) {
                U.change(i, j, C.get(i, j));
            }
        }
    }
    return U;
}

vector<double> FindUnknowns(Matrix A, vector<double> &b) {
    int32_t n = b.size();

    Matrix C, P;
    LUP(A, C, P);

    Matrix L = FindL(C);
    Matrix U = FindU(C);

    b = P.MultiplyByVector(b);
    vector<double> z(n);
    z[0] = b[0];
    for (int32_t i = 1; i < n; ++i) {
        double sum = 0;
        for (int32_t j = 0; j <= i - 1; ++j) {
            sum += L.get(i, j) * z[j];
        }
        z[i] = b[i] - sum;
    }

    vector<double> x(n);
    x[n - 1] = z[n - 1] / U.get(n - 1, n - 1);
    for (int32_t i = n - 2; i >= 0; --i) {
        double sum = 0;
        for (int32_t j = i + 1; j < n; ++j) {
            sum += U.get(i, j) * x[j];
        }
        x[i] = (z[i] - sum) / U.get(i, i);
    }

    return x;
}

#endif //LAB2_2_LUP_ALGORITHM_H
