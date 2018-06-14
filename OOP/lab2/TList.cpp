#include "TList.h"

TList::TList() : head(nullptr) {
}

std::ostream& operator<<(std::ostream& os, const TList& list) {

	if (list.empty()) {
		os << "The list is empty." << std::endl;
		return os;
	}

    TListItem *item = list.head;
    
    while(item!=nullptr)
    {
      os << *item;
      item = item->GetNext();
    }
    
    return os;
}

void TList::push(Hexagon &hexagon) {
    TListItem *tmp = new TListItem(hexagon);
    tmp->SetNext(head); // tmp->next = *head
    head = tmp;

}

void TList::pushBack(Hexagon &hexagon) {
	TListItem *other = new TListItem(hexagon);
	TListItem *iter = this->head;
	if (head != nullptr) {
		while (iter->GetNext() != nullptr) {
			iter = iter->SetNext(iter->GetNext());
		}
		iter->SetNext(other);// little bit strange
		other->SetNext(nullptr);
	}
	else {
		head = other;
	}
}

const bool TList::empty() const{
    return head == nullptr;
}

Hexagon TList::pop() {
    Hexagon result;
    if (head != nullptr) {
        TListItem *old_head = head;
        head = head->GetNext();
        result = old_head->GetHexagon();
        old_head->SetNext(nullptr);
        delete old_head;
    }

    return result;
}


Hexagon TList::getEl(int n){
	TListItem* iter = this->head;
	for (int i = 1; i < n; i++) {
		iter = iter->GetNext();
		
	}
	return iter->GetHexagon();
}

 void TList::delEl(Hexagon & hexagon)
 {
 	TListItem* iter = this->head;
 	if (iter != nullptr) {
 		if (iter->GetHexagon() == hexagon) {
 			head = nullptr;
 			std::cout << "Hexagon is deleted." << std::endl;
 		}
 		else {
 			if (!(iter->GetNext() == nullptr)) {
 				while (!(iter->GetNext() == nullptr) && !(iter->GetNext()->GetHexagon() == hexagon)) {
 					iter = iter->GetNext();
 				}
 				if (!(iter->GetNext() == nullptr)) {
 					iter->SetNext(iter->GetNext()->GetNext());
 					std::cout << "Hexagon is deleted." << std::endl;
 				}
 				else {
 					std::cout << "There is no such element!" << std::endl;
 				}
 			}
 			else {
 				std::cout << "There is no such element!" << std::endl;
 			}
 		}
 	}
 }

void TList::eraseList() {
	head = nullptr;
}

TList::~TList() {
    delete head;
}