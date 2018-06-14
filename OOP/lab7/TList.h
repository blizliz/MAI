#ifndef TLIST_H
#define	TLIST_H
#include <memory>
#include "TListItem.h"
#include "TIterator.h"
#include "TArray.h"
#include "Figure.h"

template <class T,class TT>
class TList {
public:
    TList();
    
    void Insert(std::shared_ptr<TT> &&value);
    void RemoveByType(const int type);
    size_t Size();

    bool Empty();
    
    TIterator<TListItem<T>, T> begin() const;
    TIterator<TListItem<T>, T> end() const;
    template <class A,class AA> friend std::ostream& operator<<(std::ostream& os,const TList<A,AA>& list);
    
    virtual ~TList();
private:
    std::shared_ptr<TListItem<T>> head;
    size_t size;
};

#endif	/* TLIST_H */

