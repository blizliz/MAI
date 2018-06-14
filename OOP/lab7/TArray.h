/* 
 * File:   TStack.h
 * Author: dvdemon
 *
 * Created on July 18, 2015, 7:10 PM
 */

#ifndef TSTACK_H
#define	TSTACK_H

#include "TIterator.h"
#include <memory>
#include "Figure.h"

template <class T> class TArray {
public:
    TArray();
    TArray(size_t &size);

    std::shared_ptr<T> * GetData();
    void resize(int size);
    std::shared_ptr<T> & operator [](int i);
    int GetSize();
    void pop(int i);
    void push(std::shared_ptr<T> &val);
    void  Print();

    template <class A> friend std::ostream& operator<<(std::ostream& os, TArray<A>& array);
    virtual ~TArray();
private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T> *data;
};

#endif	/* TSTACK_H */

