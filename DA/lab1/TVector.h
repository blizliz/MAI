#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <cstdlib>

struct TData {
    long phone;
    char *phoneString;
    char *value;
};

class TVector {
public:
    TVector(size_t capacity, size_t size);
    void PushBack(TData value);
    size_t GetSize();
    TData &operator[](size_t ix);
    TVector &operator = (TVector &vector);
    ~TVector();
private:
    TData *begin;
    size_t size;
    size_t capacity;
};

#endif