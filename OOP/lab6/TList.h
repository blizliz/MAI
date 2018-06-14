#ifndef TLIST_H
#define	TLIST_H

#include "TListItem.h"
#include "TIterator.h"
#include <memory>

template <class T>
class TList {
public:
	TList();

	void AddFirst(std::shared_ptr<T> &&figure);
	void AddLast(std::shared_ptr<T> &&figure);
	void Insert(size_t pos, std::shared_ptr<T> &&figure);
	void DeleteElem(size_t pos);
	bool Empty();
	void Erase();

	template <class A> friend std::ostream& operator<<(std::ostream& os, const TList<A>& list);

	TIterator<TListItem<T>, T> begin();
	TIterator<TListItem<T>, T> end();

	virtual ~TList();
private:
	std::shared_ptr<TListItem<T> > head;
};

#endif	/* TLIST_H */