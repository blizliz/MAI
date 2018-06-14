#ifndef TLIST_H
#define	TLIST_H

#include "Hexagon.h"
#include "TListItem.h"

class TList {
public:
	TList();
    
    void push(Hexagon &hexagon);
    void pushBack(Hexagon &hexagon);
    const bool empty() const;
    Hexagon getEl(int n);
    void delEl(Hexagon & hexagon);
    void eraseList();
    Hexagon pop();

    friend std::ostream& operator<<(std::ostream& os,const TList& List);
    virtual ~TList();
private:
    TListItem *head;
};

#endif	/* TLIST_H */