#ifndef TListItem_H
#define	TListItem_H
#include <memory>
#include "Figure.h"
#include "Triangle.h"
#include "Hexagon.h"
#include "Octagon.h"

class TListItem {
public:
	TListItem(const std::shared_ptr<Figure>& figure);
	friend std::ostream& operator<<(std::ostream& os, const TListItem& obj);

	std::shared_ptr<TListItem> SetNext(std::shared_ptr<TListItem> &next);
	std::shared_ptr<TListItem> GetNext();
	std::shared_ptr<Figure> GetFigure() const;

	virtual ~TListItem();
private:
	std::shared_ptr<Figure> figure;
	std::shared_ptr<TListItem> next;
};

#endif	/* TListItem_H */