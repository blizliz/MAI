#include "TVector.h"

TVector::TVector(size_t capacity, size_t size) {
    this->size = size;
    begin = new TData[capacity];
    this->capacity = capacity;
}

void TVector::PushBack(TData value) {
    if (size == capacity) {
        capacity *= 2;

        begin = (TData *)realloc(begin, sizeof(TData) * capacity);
    }
    begin[size++] = value;
}

size_t TVector::GetSize() {
    return size;
}

TVector::~TVector() {
	delete[] begin;
}

TData &TVector::operator[](size_t ix) {
    return begin[ix];        
}

TVector &TVector::operator = (TVector &vector) {
    delete [] begin;
    begin = nullptr;
    if (vector.begin != nullptr) {
        begin = new TData[vector.capacity];
        for (int ix = 0; ix < vector.size; ix++) {
            begin[ix] = vector.begin[ix];
        }
        capacity = vector.capacity;
        size = vector.size;
    }
    return *this;
}