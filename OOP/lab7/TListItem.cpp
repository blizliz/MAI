#include "TListItem.h"

template <class T> TListItem<T>::TListItem(std::shared_ptr<T> &value) {
    _value = value;
    _next = nullptr;
}

template <class T> std::shared_ptr<T> TListItem<T>::GetValue() {
    return _value;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::GetNext() {
    return _next;
}

template <class T> void TListItem<T>::SetNext(std::shared_ptr<TListItem> next) {
    _next = next;
}

template <class T>
std::ostream & operator <<(std::ostream &os, TListItem<T> &obj) {
    obj.GetValue()->Print();
    return os;
}

template <class T> TListItem<T>::~TListItem() {
}

template class TListItem< TArray<Figure> >;
template std::ostream & operator <<(std::ostream &os, TListItem< TArray<Figure> > &rhs);