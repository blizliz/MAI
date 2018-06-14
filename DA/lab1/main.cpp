#include <iostream>
#include <cmath>
#include <cstring>
#include "TVector.h"
#include <ctime>

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

void CountingSort(TVector &v, int j, int r, int numSys);
void RadixSort(TVector &v);

int main() {

    TVector v(32, 0);
    TData data;

    /*записываем данные в вектор*/
    data.phoneString = new char[17];
    while (scanf("%s", data.phoneString) != EOF) {
        /*считываем ключ как строку и параллельно записываем как число*/
        data.phone = 0;
        for (int i = 0; i < strlen(data.phoneString); i++) {
            if (data.phoneString[i] != '+' && data.phoneString[i] != '-') {
                data.phone = data.phone * 10 + (data.phoneString[i] - '0');
            }
        }
        /*считываем значение*/
        char *tmp = new char[LEN_TEXT+1];
        scanf("%s", tmp);
        data.value = new char[strlen(tmp) + 1];
        strcpy(data.value, tmp);
        delete [] tmp;
        
        v.PushBack(data);
        
        data.phoneString = new char[17];
    }

    RadixSort(v);

    /*выводим отсортированне данные*/
    for (int i = 0; i < v.GetSize(); i++) {
        cout << v[i].phoneString << '\t' << v[i].value << endl;
    }

    return 0;
}

void RadixSort(TVector &v) {
    
    if (v.GetSize() < 2) {
        return;
    }

    int r = GetSortPar(v.GetSize());                 //количество бит одного разряда
    int numSys = pow(2, r);                          //система счисления
    int phoneDigits = ceil((float)PHONES_BITS / r);  //количество разрядов

    for (int j = 0; j < phoneDigits; j++) {
        CountingSort(v, j, r, numSys);
    }
}

void CountingSort(TVector &v, int j, int r, int numSys) {
    TVector result(v.GetSize(), v.GetSize());
    
        long *C = new long[numSys];
    
        for (int i = 0; i < numSys; i++) { 
            C[i] = 0;
        }
    
        for (int i = 0; i < v.GetSize(); i++) {
            C[GetDigit(v[i].phone, r, numSys, j)] += 1;
        }
    
        for (int i = 1; i < numSys; i++) {
            C[i] = C[i] + C[i - 1];
        }
        
        for (int i = v.GetSize() - 1; i >= 0; i--) {
            result[C[GetDigit(v[i].phone, r, numSys, j)] - 1] = v[i];
            C[GetDigit(v[i].phone, r, numSys, j)] -= 1;
        }
    
        v = result;
        
        delete[] C;
}