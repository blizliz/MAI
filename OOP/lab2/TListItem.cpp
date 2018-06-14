#include "TListItem.h"
#include <iostream>

TListItem::TListItem(const Hexagon& hexagon) {
    this->hexagon = hexagon;
    this->next = nullptr;
    //std::cout << "List item: created" << std::endl;
}

TListItem* TListItem::SetNext(TListItem* next) {
    TListItem* old = this->next;
    this->next = next;
    return old;
}

Hexagon TListItem::GetHexagon() const {
    return this->hexagon;
}

TListItem* TListItem::GetNext() {
    return this->next;
}

TListItem::~TListItem() {
    std::cout << "List item: deleted" << std::endl;
    delete next;

}

std::ostream& operator<<(std::ostream& os, const TListItem& obj) {
    os << "[" << obj.hexagon << "]" << std::endl;
    return os;
}