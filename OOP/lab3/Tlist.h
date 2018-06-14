#ifndef TLIST_H
#define	TLIST_H

#include "Figure.h"
#include "TListItem.h"
#include <memory>

class TList {
public:
	TList();

	void AddFirst(std::shared_ptr<Figure> &&figure);
	void AddLast(std::shared_ptr<Figure> &&figure);
	void Insert(size_t pos, std::shared_ptr<Figure> &&figure);
	void DeleteElem(size_t pos);
	bool Empty();

	void Erase();

	friend std::ostream& operator<<(std::ostream& os, const TList& list);
	virtual ~TList();
private:

	std::shared_ptr<TListItem> head;
};

#endif	/* TLIST_H */