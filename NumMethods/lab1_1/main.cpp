#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include "Matrix.h"

using namespace std;

void PrintMatrixToFile(Matrix &A, ofstream &fout) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            fout.width(6);
            fout.precision(2);
            fout << left << A.get(i, j) << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}

void PrintVectorToFile(vector<double> &v, ofstream &fout) {
    fout << "(";
    for (int32_t i = 0; i < v.size() - 1; ++i) {
        fout << v[i] << " ";
    }
    fout << v[v.size() - 1];
    fout << ")\n\n";
}


vector<double> ReadVector(int32_t n, ifstream &fin) {
    vector<double> v(n);
    for (int32_t i = 0; i < n; ++i) {
        fin >> v[i];
    }
    return v;
}

Matrix IdentityMatrix(int32_t n) {
    Matrix E(n);
    for (int32_t i = 0; i < n; ++i) {
        E.change(i, i, 1);
    }
    return E;
}

void LUP(Matrix &A, Matrix &C, Matrix &P) {
    const int32_t n = A.size();

    C = A;
    P = IdentityMatrix(n);

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

Matrix FindInverseMatrix(Matrix &A, Matrix &L, Matrix &U,  Matrix &P, ofstream &logFile) {
    int32_t n = A.size();
    
    Matrix invA(n);

    //1)inverse matrix L calculation
    Matrix invL(n);
    for (int32_t i = 0; i < n; ++i) {
        invL.change(i, i, 1);
        for (int32_t j = 0; j < i; ++j) {
            double sum = 0;
            for (int32_t k = 0; k < i; ++k) {
                sum += L.get(i, k) * invL.get(k, j);
            }
            invL.change(i, j, -sum / L.get(i, i));
        }
    }

    //2)matrix D = invU * invL calculation
    Matrix D(n);
    for (int32_t i = n - 1; i >= 0; --i) {
        for (int32_t j = 0; j < n; ++j) {
            double sum = 0;
            for (int32_t k  = i + 1; k < n; ++k) {
                sum += U.get(i, k) * D.get(k, j);
            }
            D.change(i, j, (invL.get(i, j) - sum) / U.get(i, i));
        }
    }

    invA = D.MultiplyRight(P);
    
    return invA;
}

vector<double> FindUnknowns(vector<double> &b, Matrix &L, Matrix &U, Matrix &P) {
    int32_t n = b.size();
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

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "More arguments expected";
        return 0;
    }

    if (string(argv[1]) == "--help") {
        cout << "Expected file name where:\n";
        cout << "1 line: n(maxrix size)\n";
        cout << "next lines: elements of A matrix\n";
        cout << "last line: n elements of b vector\n";
        return 0;
    }

    ifstream matrixFile(argv[1]);
    Matrix A(matrixFile);
    int32_t n = A.size();

    vector<double> b = ReadVector(n, matrixFile);
    matrixFile.close();

    ofstream logFile("logFile");

    logFile << "Matrix A:\n";
    PrintMatrixToFile(A, logFile);

    Matrix C, P;
    LUP(A, C, P);

    Matrix L = FindL(C);
    Matrix U = FindU(C);

    logFile << "LUP matrix decomposition:\n";
    logFile << "Matrix L:\n";
    PrintMatrixToFile(L, logFile);
    logFile << "Matrix U:\n";
    PrintMatrixToFile(U, logFile);
    logFile << "Matrix P:\n";
    PrintMatrixToFile(P, logFile);

    vector<double> x = FindUnknowns(b, L, U, P);
    logFile << "Unknowns x:\n";
    PrintVectorToFile(x, logFile);

    Matrix invA = FindInverseMatrix(A, L, U, P, logFile);
    logFile << "Inverse A:\n";
    PrintMatrixToFile(invA, logFile);

    //matrix determinant
    double detA = 1;
    for (int32_t i = 0; i < n; ++i) {
        detA *= U.get(i, i);
    }
    logFile.precision(10);
    logFile << "detA = "<< detA << endl;
    logFile << "\n";

    logFile.close();
    return 0;
}