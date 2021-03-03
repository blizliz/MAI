#ifndef LAB2_2_VECTOROPERATIONS_H
#define LAB2_2_VECTOROPERATIONS_H

#include "Matrix.h"
#include <cmath>

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

vector<double> Add(const vector<double> &v1, const vector<double> &v2) {
    vector<double> res(v1.size());
    for (int32_t i = 0; i < v1.size(); ++i) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

vector<double> Subtract(const vector<double> &v1, const vector<double> &v2) {
    vector<double> res(v1.size());
    for (int32_t i = 0; i < v1.size(); ++i) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

void MultiplyByNum(vector<double> &v, double num) {
    for (int32_t i = 0; i < v.size(); ++i) {
        v[i] *= num;
    }
}


double VectorNorm(const vector<double> &v) {
    double norm = 0;
    for (int32_t i = 0; i < v.size(); ++i) {
        if (fabs(v[i]) > norm) {
            norm = fabs(v[i]);
        }
    }
    return norm;
}

#endif //LAB2_2_VECTOROPERATIONS_H
