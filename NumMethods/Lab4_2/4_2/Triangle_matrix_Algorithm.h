#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<double> FindUnknowns(const vector<double> &a, const vector<double> &b, const vector<double> &c, const vector<double> &d) {
    int32_t n = a.size();

    vector<double> p, q;
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
    return x;
}