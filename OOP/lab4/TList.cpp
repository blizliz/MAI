#include "TList.h"

template <class T>
TList<T>::TList() : head(nullptr) {
}

template <class T>
void TList<T>::AddFirst(std::shared_ptr<T> &&figure) {
	std::shared_ptr<TListItem<T>> tmp(new TListItem<T>(figure));
	tmp->SetNext(head);
	head = tmp;

	std::cout << "Figure added." << std::endl;
}

template <class T>
void TList<T>::AddLast(std::shared_ptr<T> &&figure) {
	std::shared_ptr<TListItem<T> > tmp(new TListItem<T>(figure));
	std::shared_ptr<TListItem<T> > last = head;
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
	std::cout << "Hexagon added." << std::endl;
}

template <class T> void TList<T>::Insert(size_t pos, std::shared_ptr<T> &&figure) {
	std::shared_ptr<TListItem<T>> tmp(new TListItem<T>(figure));
	if (head != nullptr) {
		std::shared_ptr<TListItem<T>> prev = head;
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
	std::cout << "Hexagon added." << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TList<T>& list) {

	std::shared_ptr<TListItem<T>> item = list.head;

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

template <class T>
void TList<T>::DeleteElem(size_t pos) {
	if (head != nullptr) {
		std::shared_ptr<TListItem<T>> tmp = head;
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

template <class T>
bool TList<T>::Empty() {
	return head == nullptr;
}

template <class T>
void TList<T>::Erase() {
	if (head != nullptr) {
		head = nullptr;
	}
	else {
		std::cout << "List is empty!" << std::endl;
	}
}

template <class T> TList<T>::~TList() {
	//delete head;
}

#include "Figure.h"
template class TList<Figure>;
template std::ostream& operator<<(std::ostream& os, const TList<Figure>& stack);