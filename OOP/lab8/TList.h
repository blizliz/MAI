#ifndef TLIST_H
#define	TLIST_H

#include "TListItem.h"
#include "TIterator.h"
#include <future>
#include <mutex>
#include"Figure.h"

template <class T>
class TList {
public:
	TList();

	void AddFirst(std::shared_ptr<T> figure);
	void AddLast(std::shared_ptr<T> figure);
	void Insert(size_t pos, std::shared_ptr<T> figure);
	void DeleteElem(size_t pos);
	bool Empty();
	void Erase();
	size_t size();

	void push(std::shared_ptr<T> &&item);

	std::shared_ptr<T> operator[] (size_t i);
	void sort();
	void sort_parallel();

	std::shared_ptr<T> pop();
	std::shared_ptr<T> pop_last();

	template <class A> friend std::ostream& operator<<(std::ostream& os, const TList<A>& list);

	TIterator<TListItem<T>, T> begin();
	TIterator<TListItem<T>, T> end();

	virtual ~TList();
private:
	std::future<void> sort_in_background();
	std::shared_ptr<TListItem<T> > head;

	size_t _size;
};

#endif	/* TLIST_H */