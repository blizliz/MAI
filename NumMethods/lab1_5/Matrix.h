#ifndef LAB1_1_MATRIX_H
#define LAB1_1_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>

using  namespace std;

class Matrix {
public:
    Matrix() {}
    Matrix(int32_t n);
    Matrix(ifstream &fin);

    double get(int32_t i, int32_t j);
    void change(int32_t i, int32_t j, double val);

    Matrix MultiplyRight(Matrix &other);
    vector<double> MultiplyByVector(vector<double> &v);
    Matrix MultiplyByNumber(double num);

    void SwapLines(int32_t inx1, int32_t inx2);

    Matrix Subtract(Matrix &other);
    void Resize(int32_t n);
    int32_t size();

private:
    vector<vector<double>> data;
};

#endif //LAB1_1_MATRIX_H
