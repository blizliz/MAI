#include "TListItem.h"
#include <iostream>

template <class T>
TListItem<T>::TListItem(const std::shared_ptr<T>& item) {
	this->item = item;
	this->next = nullptr;
	std::cout << "List item created" << std::endl;
}

template <class T>  TAllocationBlock TListItem<T>::listitem_allocator(sizeof(TListItem<T>), 100);

template <class T>
std::shared_ptr<TListItem<T>> TListItem<T>::SetNext(std::shared_ptr<TListItem<T>> &next) {
	std::shared_ptr<TListItem<T>> old = this->next;
	this->next = next;
	return old;
}

template <class T>
std::shared_ptr<T> TListItem<T>::GetValue() const {
	return this->item;
}

template <class T>
std::shared_ptr<TListItem<T>> TListItem<T>::GetNext() {
	return this->next;
}

template <class T> void * TListItem<T>::operator new (size_t size) {
	return listitem_allocator.allocate();
}


template <class T> void TListItem<T>::operator delete(void *p) {

	listitem_allocator.deallocate(p);
}

template <class T> TListItem<T>::~TListItem() {
	std::cout << "List item deleted" << std::endl;
	//delete next;

}

template <class A> std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj) {
	os << "[" << obj.item << "]" << std::endl;
	return os;
}

#include "Figure.h"
template class TListItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const TListItem<Figure>& obj);