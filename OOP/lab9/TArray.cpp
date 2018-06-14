#include "TArray.h"

template <class T> TArray<T>::TArray() : size(0), capacity(5){
    data = new std::shared_ptr<T>[capacity];
   // std::cout << "Array created" << std::endl;
}

template <class T>
TArray<T>::TArray(size_t size) {
    this->capacity = size;
    this->size = 0;
    data = new std::shared_ptr<T>[size];
}

template <class T>
std::shared_ptr<T> * TArray<T>::GetData() {
    return data;
}

template<class T>
void TArray<T>::resize(int size) {
    this->capacity = size;
    size = 0;
    delete [] data;
    data = new std::shared_ptr<T>[size];
}

template <class T>
std::shared_ptr<T> & TArray<T>::operator [](int i) {
    return data[i];
}

template<class T>
int TArray<T>::GetSize() {
    return size;
}

template<class T>
std::shared_ptr<T> & TArray<T>::pop() {
	--size;
	return data[size];
}

template<class T>
void TArray<T>::push(std::shared_ptr<T> &&val) {
	data[size] = val;
	++size;
}

template <class T> TArray<T>::~TArray() {
    delete [] data;
std::cout << "Array deleted" << std::endl;
}

template class TArray<Figure>;
template class TArray<char>;
template class TArray<void *>;
template class TArray<int>;
template class TArray< std::function<void(void)> >;