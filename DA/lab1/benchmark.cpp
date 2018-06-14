#include <algorithm>
#include <cassert>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

const size_t PHONES_BITS = 45; // Количество бит в номере
const size_t LEN_TEXT = 2048;  // Максимальная длина строки-значения

inline int Log(size_t a, size_t b) {
    return (int)(log(b) / log(a));
}

inline int GetDigit(long n, int r, int numSys, int i) { // получить разряд по r
    return (n >> (r * i)) & (numSys - 1);
}

inline int GetSortPar(long n) {                         //кол-во бит каждого разряда
    if (PHONES_BITS < Log(2, n)) {
        return PHONES_BITS;
    } else {
        return (int)Log(2, n);
    }
}

void CountingSort(vector<pair<pair<long,char *>, char *>> &v, int j, int r, int numSys);
void RadixSort(vector<pair<pair<long,char *>, char *>> &v);

bool CheckOrder(const vector<pair<pair<long,char *>, char *>>& data) {
    for (size_t idx = 1; idx < data.size(); ++idx) {
        if (data[idx - 1] > data[idx]) {
            return false;
        }
    }
    return true;
}

void StdSort(vector<pair<pair<long,char *>, char *>>& data) {
    std::sort(data.begin(), data.end());
}

void RunSort(vector<pair<pair<long,char *>, char *>>& data, std::string type) {
    time_t start = time(0);
    if (type == "radix") {
        RadixSort(data); 
    } else if (type == "std") {
        StdSort(data);
    } else {
        std::cerr << "Unknown type of sorting" << std::endl;
        return;
    }
    time_t end = time(0);
    assert(CheckOrder(data) == true);
    std::cout << "Time of working " << type << ": " << (end - start) / 1000.0 << std::endl;
}

int main(int argc, const char* argv[]) {

    if (argc != 4) {
        std::cerr << "Usage: ./benchmark count sort1 sort2" << std::endl;
        return 0;
    }

    size_t size = atoi(argv[1]);

    //pair<pair<long,char *>, char *> p;
    vector<pair<pair<long,char *>, char *>> data;
    data.resize(size);

    const int maxNum = 1000000;
    for (size_t idx = 0; idx < size; ++idx) {
        data[idx].first.first = rand() % maxNum;
    }

    vector<pair<pair<long,char *>, char *>> dataCopy(data);

    RunSort(data, std::string(argv[2]));
    RunSort(dataCopy, std::string(argv[3]));

    return 0;
}

void RadixSort(vector<pair<pair<long,char *>, char *>> &v) {
    
    if (v.size() < 2) {
        return;
    }

    int r = GetSortPar(v.size());                 //количество бит одного 
    int numSys = pow(2, r);                          //система счисления
    int phoneDigits = ceil((float)PHONES_BITS / r);  //количество разрядов

    for (int j = 0; j < phoneDigits; j++) {
        CountingSort(v, j, r, numSys);
    }
}

void CountingSort(vector<pair<pair<long, char *>, char *>> &v, int j, int r, int numSys) {

    vector<pair<pair<long, char *>, char *>> result(v.size());

    long *C = new long[numSys];

    for (int i = 0; i < numSys; i++) {
        C[i] = 0;
    }

    for (int i = 0; i < v.size(); i++) {
        ++C[GetDigit(v[i].first.first, r, numSys, j)];
    }

    for (int i = 1; i < numSys; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        result[C[GetDigit(v[i].first.first, r, numSys, j)] - 1] = v[i];
        --C[GetDigit(v[i].first.first, r, numSys, j)];
    }

    v = result;

    delete[] C;
}