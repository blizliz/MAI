#include "Matrix.h"

Matrix::Matrix(int32_t n) {
    for (int32_t i = 0; i < n; ++i) {
        vector<double> v(n);
        data.push_back(v);
    }
}
Matrix::Matrix(ifstream &fin) {
    int32_t n;
    fin >> n;
    for (int32_t i = 0; i < n; ++i) {
        vector<double> v;
        for (int32_t j = 0; j < n; ++j) {
            int32_t el;
            fin >> el;
            v.push_back(el);
        }
        data.push_back(v);
    }
}

double Matrix::get(int32_t i, int32_t j) {
    return data[i][j];
}

void Matrix::change(int32_t i, int32_t j, double val) {
    data[i][j] = val;
}

Matrix Matrix::MultiplyRight(Matrix &other) {
    int32_t n = data.size();
    Matrix res(n);
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            double el = 0;
            for (int32_t k = 0; k < n; ++k) {
                el += this->get(i, k) * other.get(k, j);
            }
            res.change(i, j, el);
        }
    }
    return res;
}

vector<double> Matrix::MultiplyByVector(vector<double> &v) {
    int32_t n = this->size();
    vector<double> res(n);
    for (int32_t i = 0; i < n; ++i) {
        double el = 0;
        for (int32_t j = 0; j < n; ++j) {
            el += this->get(i, j) * v[j];
        }
        res[i] = el;
    }
    return res;
}

void Matrix::SwapLines(int32_t inx1, int32_t inx2) {
    iter_swap(data.begin() + inx1, data.begin() + inx2);
}

int32_t Matrix::size() {
    return data.size();
}

Matrix Matrix::Subtract(Matrix &other) {
    int32_t n = data.size();
    Matrix res(n);
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            double el = this->get(i, j) - other.get(i, j);
            res.change(i, j, el);
        }
    }
    return res;
}

void Matrix::Resize(int32_t n) {
    data.clear();
    for (int32_t i = 0; i < n; ++i) {
        vector<double> v(n);
        data.push_back(v);
    }
}
