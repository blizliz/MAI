#ifndef TListItem_H
#define	TListItem_H

#include "Hexagon.h"
class TListItem {
public:
    TListItem(const Hexagon& hexagon);
    friend std::ostream& operator<<(std::ostream& os, const TListItem& obj);
    
    TListItem* SetNext(TListItem* next);
    TListItem* GetNext();
    Hexagon GetHexagon() const;

    virtual ~TListItem();
private:
    Hexagon hexagon;
    TListItem *next;
    TListItem *prev;
};

#endif	/* TListItem_H */