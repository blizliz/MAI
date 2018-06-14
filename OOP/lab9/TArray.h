#ifndef TSTACK_H
#define	TSTACK_H

#include "TIterator.h"
#include <memory>
#include "Figure.h"
#include <functional>

template <class T> 
class TArray {
public:
    TArray();
    TArray(size_t size);

    std::shared_ptr<T> * GetData();
    void resize(int size);
    std::shared_ptr<T> & operator [](int i);
    int GetSize();
	std::shared_ptr<T> & pop();
    void push(std::shared_ptr<T> &&val);

    void  Print();

    virtual ~TArray();
private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T> *data;
};

#endif	/* TSTACK_H */

