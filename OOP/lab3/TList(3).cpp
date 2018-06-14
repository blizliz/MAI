#include "stdafx.h"
#include "TList.h"

TList::TList() : head(nullptr) {
}

void TList::AddFirst(std::shared_ptr<Figure> &&figure) {
	std::shared_ptr<TListItem> tmp(new TListItem(figure));
	tmp->SetNext(head);
	head = tmp;

	std::cout << "Figure added." << std::endl;
}

void TList::AddLast(std::shared_ptr<Figure> &&figure) {
	std::shared_ptr<TListItem> tmp(new TListItem(figure));
	std::shared_ptr<TListItem> last = head;
	if (head != nullptr) {
		while (last->GetNext() != nullptr) {
			last = last->SetNext(last->GetNext());
		}
		last->SetNext(tmp);
		//tmp->SetNext(nullptr);
	}
	else {
		head = tmp;
	}
	std::cout << "Figure added." << std::endl;
}

void TList::Insert(size_t pos, std::shared_ptr<Figure> &&figure) {
	std::shared_ptr<TListItem> tmp(new TListItem(figure));
	if (head != nullptr) {
		std::shared_ptr<TListItem> prev = head;
		while ((pos > 2) && (prev->GetNext() != nullptr)) {
			prev = prev->SetNext(prev->GetNext());
			pos--;
		}
		tmp->SetNext(prev->GetNext());
		prev->SetNext(tmp);
	}
	else {
		head = tmp;
	}
	std::cout << "Figure added." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TList& list) {

	std::shared_ptr<TListItem> item = list.head;

	while (item != nullptr)
	{
		std::cout << "[ ";
		item->GetFigure()->Print();
		std::cout << " ] ";
		//os << item;
		item = item->GetNext();
	}

	std::cout << std::endl;
	return os;
}

void TList::DeleteElem(size_t pos) {
	if (head != nullptr) {
		std::shared_ptr<TListItem> tmp = head;
		if (pos == 1) {
			head = tmp->GetNext();
		}
		else {
			while ((pos > 2) && (tmp->GetNext() != nullptr)) {
				tmp = tmp->GetNext();
				pos--;
			}
			if (tmp->GetNext() != nullptr) {
				tmp->SetNext(tmp->GetNext()->GetNext());
			}
		} 
	}
	else {
		std::cout << "Error: List is empty!" << std::endl;
	}
}

bool TList::Empty() {
	return head == nullptr;
}

void TList::Erase() {
	if (head != nullptr) {
		head = nullptr;
	}
	else {
		std::cout << "List is empty!" << std::endl;
	}
}

TList::~TList() {
	//delete head;
}