#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "Matrix.h"

using namespace std;

double MatrixNorm(Matrix &A) {
    double norm = 0;
    for (int32_t i = 0; i < A.size(); ++i) {
        double sum = 0;
        for (int32_t j = 0; j < A.size(); ++j) {
            sum += abs(A.get(i, j));
        }
        if (sum > norm) {
            norm = sum;
        }
    }
    return norm;
}

double VectorNorm(const vector<double> &v) {
    double norm = 0;
    for (int32_t i = 0; i < v.size(); ++i) {
        if (abs(v[i]) > norm) {
            norm = abs(v[i]);
        }
    }
    return norm;
}

vector<double> diff(vector<double> &v1, vector<double> &v2) {
    vector<double> res;
    for (int32_t i = 0; i < v1.size(); ++i) {
        res.push_back(v1[i] - v2[i]);
    }
    return res;
}

struct Equivlent {
    Equivlent(int32_t n) {
        Alpha.Resize(n);
        beta.assign(n, 0);
    }
    Matrix Alpha;
    vector<double> beta;
};

void IterativeMethod(Matrix &A, vector<double> &b, Equivlent &equiv, double eps, ofstream &fout) {
    int32_t n = A.size();

    //finding alpha matrix norm
    double alphaNorm = MatrixNorm(equiv.Alpha);
    vector<double> x(n);
    x = equiv.beta;
    if (alphaNorm < 1) {
        fout << "Alpha matrix norm < 1\n";

        double endCond;
        int32_t itNum = 1;
        do {
            //X(k) = beta + alpha * X(k - 1)
            vector<double> nextX(n);
            for (int32_t i = 0; i < n; ++i) {
                double sum = 0;
                for (int32_t j = 0; j < n; ++j) {
                    sum += equiv.Alpha.get(i, j) * x[j];
                }
                nextX[i] = equiv.beta[i] + sum;
            }

            //current error estimate
            vector<double> diffX = diff(nextX, x);
            endCond = alphaNorm / (1 - alphaNorm) * VectorNorm(diffX);

            x = nextX;
            ++itNum;
        } while (endCond > eps);

        fout << "Nnumber of iterations = " << itNum << "\n";
    } else if (alphaNorm == 1) {
        fout << "Alpha matrix norm = 1\n";

        double endCond;
        int32_t itNum = 1;
        do {
            //X(k) = beta + alpha * X(k - 1)
            vector<double> nextX(n);
            for (int32_t i = 0; i < n; ++i) {
                double sum = 0;
                for (int32_t j = 0; j < n; ++j) {
                    sum += equiv.Alpha.get(i, j) * x[j];
                }
                nextX[i] = equiv.beta[i] + sum;
            }

            //current error estimate
            vector<double> diffX = diff(nextX, x);
            endCond = VectorNorm(diffX);

            x = nextX;
            ++itNum;
        } while (endCond > eps);

        fout << "Nnumber of iterations = " << itNum << "\n";
    }

    fout << "Unknowns x:\n";
    for (int32_t i = 0; i < n; ++i) {
        fout << "x" << i + 1 << " = " << x[i] << "\n";
    }
    fout << "\n\n";
}

void SeidelMethod(Matrix &A, vector<double> &b, Equivlent &equiv, double eps, ofstream &fout) {
    int32_t n = A.size();
    vector<double> x = equiv.beta;

    Matrix E(n), B(n), C(n);
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            if (i == j) {
                E.change(i, j, 1);
                C.change(i, j, equiv.Alpha.get(i, j));
            } else if (i < j) {
                C.change(i, j, equiv.Alpha.get(i, j));
            } else {
                B.change(i, j, equiv.Alpha.get(i, j));
            }
        }
    }

    double alphaNorm = MatrixNorm(equiv.Alpha);
    if (alphaNorm < 1) {
        fout << "Alpha matrix norm < 1\n";

        double endCond;
        vector<double> nextX(n);
        int32_t itNum = 1;

        do {
            for (int32_t i = 0; i < n; ++i) {    //matrix line
                double sum = 0;
                for (int j = 0; j < i; ++j) {
                    sum += equiv.Alpha.get(i, j) * nextX[j];
                }
                for (int j = i; j < n; ++j) {
                    sum += equiv.Alpha.get(i, j) * x[j];
                }
                nextX[i] = equiv.beta[i] + sum;
            }

            //current error estimate
            vector<double> diffX = diff(nextX, x);
            endCond = MatrixNorm(C) / (1 - alphaNorm) * VectorNorm(diffX);

            x = nextX;
            ++itNum;
        } while (endCond > eps);

        fout << "Nnumber of iterations = " << itNum << "\n";
    } else if (alphaNorm == 1) {
        fout << "Alpha matrix norm = 1\n";

        double endCond;
        vector<double> nextX(n);
        int32_t itNum = 1;

        do {
            for (int32_t i = 0; i < n; ++i) {    //matrix line
                double sum = 0;
                for (int j = 0; j < i; ++j) {
                    sum += equiv.Alpha.get(i, j) * nextX[j];
                }
                for (int j = i; j < n; ++j) {
                    sum += equiv.Alpha.get(i, j) * x[j];
                }
                nextX[i] = equiv.beta[i] + sum;
            }

            vector<double> diffX = diff(nextX, x);
            endCond = VectorNorm(diffX);
            x = nextX;
            ++itNum;
        } while (endCond > eps);

        fout << "Nnumber of iterations = " << itNum << "\n";
    }

    fout << "Unknowns x:\n";
    for (int32_t i = 0; i < n; ++i) {
        fout << "x" << i + 1 << " = " << x[i] << "\n";
    }
    fout << "\n";
}

void PrintMatrixToFile(Matrix &A, ofstream &fout) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            fout.width(6);
            fout.precision(3);
            fout << left << A.get(i, j) << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}

void PrintVectorToFile(const vector<double> v, ofstream &fout) {
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

Equivlent FindEquivalentSystem(Matrix &A, vector<double> &b) {
    int32_t n = A.size();

    Equivlent equiv(n);

    for (int32_t i = 0; i < n; ++i) {
        //check zero element and then swap lines
        if (A.get(i, i) == 0) {
            bool swapFlag = false;
            for (int32_t j = i + 1; j < n; ++j) {
                if (A.get(j, i) != 0) {
                    A.SwapLines(j, i);
                    iter_swap(b.begin() + j, b.begin() + i);
                    swapFlag = true;
                    break;
                }
            }
            if (!swapFlag) {
                continue;
            }
        }

        equiv.beta[i] = b[i] / A.get(i, i);
        for (int32_t j = 0; j < n; ++j) {
            if (i == j) {
                equiv.Alpha.change(i, j, 0);
            } else {
                equiv.Alpha.change(i, j, -A.get(i, j) / A.get(i, i));
            }
        }
    }

    return  equiv;
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

    //finding beta and alpha in x = beta + alpha * x
    Equivlent equiv = FindEquivalentSystem(A, b);

    logFile << "Matrix alpha:\n";
    PrintMatrixToFile(equiv.Alpha, logFile);

    logFile << "Vector beta:\n";
    PrintVectorToFile(equiv.beta, logFile);

    double eps;
    cout << "Set accuracy: ";
    cin >> eps;
    logFile << "Accuracy = " << eps << "\n\n";

    logFile << "ITERATIVE METHOD\n";
    IterativeMethod(A, b, equiv, eps, logFile);
    logFile << "SEIDEL METHOD\n";
    SeidelMethod(A, b, equiv, eps, logFile);
    return 0;
}