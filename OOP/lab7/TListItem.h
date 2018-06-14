#ifndef TLISTITEM_H
#define	TLISTITEM_H
#include <memory>
#include "Figure.h"
#include "TArray.h"

template <class T> class TListItem {
public:
    TListItem(std::shared_ptr<T> &);

    std::shared_ptr<T> GetValue();
    std::shared_ptr<TListItem<T>> GetNext();
    void SetNext(std::shared_ptr<TListItem<T>> next);

    template <class A>
    friend std::ostream & operator <<(std::ostream &os, TListItem<A> &obj);
    virtual ~TListItem();
private:
    std::shared_ptr<T> _value;
    std::shared_ptr<TListItem<T>> _next;

};

#endif	/* TLISTITEM_H */

