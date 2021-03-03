#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <complex>
#include <algorithm>
#include "Matrix.h"
#include "Print.h"

using namespace std;

struct QR {
    QR(int32_t n) {
        Q.Resize(n);
        R.Resize(n);
    }
    Matrix Q, R;
};

int8_t sign(double val) {
    if (val > 0) {
        return 1;
    } else if (val < 0) {
        return -1;
    } else {
        return 0;
    }
}

Matrix ColumnMultByLine(vector<double> &vLine, vector<double> &vColumn) {
    Matrix res(vLine.size());
    for (int32_t i = 0; i < vLine.size(); ++i) {
        for (int32_t j = 0; j < vLine.size(); ++j) {
            double el = vColumn[i] * vLine[j];
            res.change(i, j, el);
        }
    }
    return res;
}

double LineMultByColumn(vector<double> &vLine, vector<double> &vColumn) {
    double res = 0;
    for (int32_t i = 0; i < vLine.size(); ++i) {
        res += vColumn[i] * vLine[i];
    }
    return res;
}


QR FindQRDecomposition(Matrix &A, ofstream &logFile) {
    int32_t n = A.size();
    QR decomp(n);

    for (int32_t i = 0; i < n; ++i) {
        decomp.Q.change(i, i, 1);
    }

    for (int32_t k = 0; k < n - 1; ++k) {
        vector<double> v(n);
        //k vector norm
        double sum = 0;
        for (int j = k; j < n; ++j) {
            sum += A.get(j, k) *  A.get(j, k);
        }
        double norm = sqrt(sum);

        //v vector for Householder matrix
        v[k] = A.get(k, k) + sign(A.get(k, k)) * norm;
        for (int32_t i = k + 1; i < n; ++i) {
            v[i] = A.get(i, k);
        }
        logFile << "Vector v" << k + 1 << ":\n";
        PrintVectorToFile(v, logFile);

        Matrix E(n);
        for (int32_t i = 0; i < n; ++i) {
            E.change(i, i, 1);
        }

        //Householder matrix
        Matrix tmp(n);
        tmp = ColumnMultByLine(v, v);
        tmp = tmp.MultiplyByNumber(2 / LineMultByColumn(v, v));

        Matrix H(n);
        H = E.Subtract(tmp);
        logFile << "Matrix H" << k + 1 << ":\n";
        PrintMatrixToFile(H, logFile);

        decomp.Q = decomp.Q.MultiplyRight(H);

        A = H.MultiplyRight(A);
        logFile << "Matrix A" << k + 1 << ":\n";
        PrintMatrixToFile(A, logFile);
    }
    decomp.R = A;
    logFile << "QR matrix decomposition:\n";
    logFile << "Matrix Q:\n";
    PrintMatrixToFile(decomp.Q, logFile);
    logFile << "Matrix R:\n";
    PrintMatrixToFile(decomp.R, logFile);

    return decomp;
}

complex<double> fplus(vector<vector<complex<double>>> &a) {
    complex<double> d = sqrt(pow(a[0][0] + a[1][1], 2) - (complex<double>)4 * (a[0][0] * a[1][1] - a[1][0] * a[0][1]));
    complex<double> res = (a[0][0] + a[1][1] + d) / complex<double>(2);
    return res;
}

complex<double> fminus(vector<vector<complex<double>>> &a) {
    complex<double> d = sqrt(pow(a[0][0] + a[1][1], 2) - (complex<double>)4 * (a[0][0] * a[1][1] - a[1][0] * a[0][1]));
    complex<double> res = (a[0][0] + a[1][1] - d) / complex<double>(2);
    return res;
}

double VectorNorm(Matrix &A, int32_t from, int32_t col) {
    double sum = 0;
    for (int32_t j = from; j < A.size(); ++j) {
        sum += A.get(j, col) * A.get(j, col);
    }
    return sqrt(sum);
}

vector<complex<double>> FindEigenvalues(Matrix &A, ofstream &logFile) {
    double eps;
    cout << "Set accuracy: ";
    cin >> eps;
    logFile << "Accuracy = " << eps << "\n\n";

    int32_t n = A.size();

    vector<complex<double>> eigenvalues(n);
    int32_t itNum = 1;

    for (int32_t i = 0; i < n; ++i) {
        logFile << "_______________________________Iteration " << itNum << ":\n";
        QR decomp = FindQRDecomposition(A, logFile);
        A = decomp.R.MultiplyRight(decomp.Q);

        logFile << "Matrix A" << itNum << ":\n";
        PrintMatrixToFile(A, logFile);

        if (VectorNorm(A, i + 1, i) <= eps || i == n - 1) {
            eigenvalues[i] = A.get(i, i);
        } else {
            if (VectorNorm(A, i + 2, i) <= eps) {
                vector<vector<complex<double>>> square(2, vector<complex<double>>(2));
                square[0][0] = A.get(i, i);
                square[0][1] = A.get(i, i + 1);
                square[1][0] = A.get(i + 1, i);
                square[1][1] = A.get(i + 1, i + 1);
                complex<double> tmpL1 = fplus(square);
                complex<double> tmpL2 = fminus(square);

                logFile << "_______________________________Iteration " << ++itNum << ":\n";
                QR decomp = FindQRDecomposition(A, logFile);
                A = decomp.R.MultiplyRight(decomp.Q);

                square[0][0] = A.get(i, i);
                square[0][1] = A.get(i, i + 1);
                square[1][0] = A.get(i + 1, i);
                square[1][1] = A.get(i + 1, i + 1);
                complex<double> L1 = fplus(square);
                complex<double> L2 = fminus(square);

                if (fabs(L1 - tmpL1) <= eps && fabs(L2 - tmpL2) <= eps) {
                    eigenvalues[i] = L1;
                    eigenvalues[i + 1] = L2;
                    ++i;
                } else {
                    --i;
                }
            } else {
                --i;
            }
        }
        ++itNum;
    }

    return eigenvalues;
}

void PrintEigenvaluesToFile(vector<complex<double>> &v, ofstream &fout) {
    fout << "Eigenvalues of A matrix:\n";
    fout << "(";
    for (int32_t i = 0; i < v.size() - 1; ++i) {
        fout << v[i].real() << " + " << v[i].imag() << "i" << ", ";
    }
    fout << v[v.size() - 1].real() << " + " << v[v.size() - 1].imag() << "i";
    fout << ")\n\n";
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

    vector<complex<double>> eigenvalues = FindEigenvalues(A, logFile);
    PrintEigenvaluesToFile(eigenvalues, logFile);

    logFile.close();
    return 0;
}