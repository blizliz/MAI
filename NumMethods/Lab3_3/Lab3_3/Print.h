#ifndef LAB1_5_PRINT_H
#define LAB1_5_PRINT_H

#include "Matrix.h"

void PrintMatrixToFile(Matrix &A, ofstream &fout) {
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

#endif //LAB1_5_PRINT_H
