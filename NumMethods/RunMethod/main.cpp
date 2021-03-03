#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "More arguments expected";
        return 0;
    }
    if (string(argv[1]) == "--help") {
        cout << "Expected file where:\n";
        cout << "1 line: roots number\n";
        cout << "2 line: bottom diagonal coefficients\n";
        cout << "3 line: central diagonal coefficients\n";
        cout << "5 line: top diagonal coefficients\n";
        cout << "6 line: right coefficients\n";
        return 0;
    }
    ifstream matrixFile(argv[1]);
    int32_t n;
    matrixFile >> n;
    vector<double> a(n), b(n), c(n), d(n), p, q;

    a[0] = 0;
    for (int32_t i = 1; i < n; ++i) {
        matrixFile >> a[i];
    }
    for (int32_t i = 0; i < n; ++i) {
        matrixFile >> b[i];
    }
    for (int32_t i = 0; i < n - 1; ++i) {
        matrixFile >> c[i];
    }
    c[n - 1] = 0;
    for (int32_t i = 0; i < n; ++i) {
        matrixFile >> d[i];
    }

    double p0 = -c[0] / b[0];
    double q0 = d[0] / b[0];
    p.push_back(p0);
    q.push_back(q0);

    for (int i = 1; i < d.size(); ++i) {
        double pTmp = -c[i] / (b[i] + a[i] * p[i - 1]);
        p.push_back(pTmp);
        double qTmp = (d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
        q.push_back(qTmp);
    }

    --n;
    vector<double> x(d.size());
    x[n] = q[n];
    for (int i = n - 1; i >= 0; --i) {
        x[i] = (-c[i] * x[i + 1] / (b[i] + a[i] * p[i - 1]))
                + (d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
    }

    for (double i = 0; i < x.size(); ++i) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
    return 0;
}