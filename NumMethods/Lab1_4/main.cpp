#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Matrix.h"

using namespace std;

pair<int32_t, int32_t> MaxNotDiagonalEl(Matrix A) {
    int32_t n = A.size();
    double max = A.get(0, 1);
    pair<int32_t, int32_t> inxs = make_pair(0, 1);
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i + 1; j < n; ++j) {
            if (abs(A.get(i, j)) > max) {
                max = abs(A.get(i, j));
                inxs.first = i;
                inxs.second = j;
            }
            max = abs(A.get(i, j)) > max ? abs(A.get(i, j)) : max;
        }
    }
    return inxs;
}

Matrix RotationMatrix(int32_t l, int32_t m, Matrix A) {
    double theta;
    if (A.get(l, l) == A.get(m, m)) {
        theta = M_PI_4;
    } else {
        theta = 0.5 * atan(2 * A.get(l, m) / (A.get(l, l) - A.get(m, m)));
    }
    int32_t n = A.size();
    Matrix res(n);
    for (int32_t i = 0; i < n; ++i) {
        if (i == l || i == m) {
            res.change(i, i, cos(theta));
        } else {
            res.change(i, i, 1);
        }
    }
    res.change(l, m, -sin(theta));
    res.change(m, l, sin(theta));
    return res;
}

double CheckEndCondition(Matrix A) {
    int32_t n = A.size();
    double sum = 0;
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i + 1; j < n; ++j) {
            sum += A.get(i, j) * A.get(i, j);
        }
    }
    return sqrt(sum);
}

void PrintMatrixToFile(Matrix A, ofstream &fout) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            fout.width(10);
            fout.precision(3);
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

Matrix IdentityMatrix(int32_t n) {
    Matrix E(n);
    for (int32_t i = 0; i < n; ++i) {
        E.change(i, i, 1);
    }
    return E;
}

void JacobiAlgorithm(Matrix &A, Matrix &U, ofstream &logFile) {
    double eps;
    cout << "Set accuracy: ";
    cin >> eps;
    logFile << "Accuracy = " << eps << "\n\n";

    int32_t itNum = 1;
    double endCond;
    do {
        logFile << "_______________________________Iteration #" << itNum << ":\n";
        logFile << "Max not diagonal element of A:\n";
        int32_t l = MaxNotDiagonalEl(A).first;
        int32_t m = MaxNotDiagonalEl(A).second;
        logFile << "A[" << l << "][" << m << "] = " << A.get(l, m) <<"\n\n";

        Matrix nextU = RotationMatrix(l, m, A);
        logFile << "Matrix U" << itNum - 1 << ":\n";
        PrintMatrixToFile(nextU, logFile);

        Matrix nextUTrans = nextU;
        nextUTrans.change(l, m, -nextU.get(l, m));
        nextUTrans.change(m, l, -nextU.get(m, l));
        A = nextUTrans.MultiplyRight(A).MultiplyRight(nextU);

        logFile << "Matrix A" << itNum << ":\n";
        PrintMatrixToFile(A, logFile);

        U = U.MultiplyRight(nextU);

        endCond = CheckEndCondition(A);
        ++itNum;
    } while(endCond > eps);
}

vector<double> GetEigenvalues(Matrix &A) {
    int32_t n = A.size();
    vector<double> eigenvalues(n);
    for (int32_t i = 0; i < n; ++i) {
        eigenvalues[i] = A.get(i, i);
    }
    return eigenvalues;
}

void MultiplyVectorByNum(vector<double> &v, double num) {
    for (int32_t i = 0; i < v.size(); ++i) {
        v[i] *= num;
    }
}

void Check(Matrix &A, Matrix &evect, vector<double> &eval, ofstream &logFile) {
    int32_t n = eval.size();
    for (int32_t i = 0; i < n; ++i) {
        logFile << "____________________________Check #" << i + 1 << "\n";
        vector<double> x(n);
        for (int32_t j = 0; j < n; ++j) {
            x[j] = evect.get(j, i);
        }
        logFile << "A*x:";
        vector<double> Ax = A.MultiplyByVector(x);
        PrintVectorToFile(Ax, logFile);

        logFile << "lambda*x:";
        MultiplyVectorByNum(x, eval[i]);
        PrintVectorToFile(x, logFile);
    }
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
        return 0;
    }

    ifstream matrixFile(argv[1]);
    Matrix A(matrixFile);
    matrixFile.close();

    ofstream logFile("logFile");
    logFile << "Matrix A:\n";
    PrintMatrixToFile(A, logFile);

    int32_t n = A.size();
    Matrix U = IdentityMatrix(n);

    JacobiAlgorithm(A, U, logFile);

    vector<double> eigenvalues = GetEigenvalues(A);
    logFile << "Eigenvalues:\n";
    PrintVectorToFile(eigenvalues, logFile);
    logFile << "\n\n";

    logFile << "Eigenvectors:\n";
    PrintMatrixToFile(U, logFile);

    logFile << "Check:\n\n";
    Check(A, U, eigenvalues, logFile);

    logFile.close();
    return 0;
}