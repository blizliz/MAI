#ifndef LAB1_5_PRINT_H
#define LAB1_5_PRINT_H

#include <vector>

using namespace std;

void PrintVectorToFile(vector<double> &v, ofstream &fout) {
    fout << "(";
    for (int32_t i = 0; i < v.size() - 1; ++i) {
        fout << v[i] << " ";
    }
    fout << v[v.size() - 1];
    fout << ")\n\n";
}

#endif //LAB1_5_PRINT_H
