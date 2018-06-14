#include "stdafx.h"
#include "TListItem.h"
#include <iostream>

TListItem::TListItem(const std::shared_ptr<Figure>& figure) {
	this->figure = figure;
	this->next = nullptr;
	//std::cout << "List item created" << std::endl;
}

std::shared_ptr<TListItem> TListItem::SetNext(std::shared_ptr<TListItem> &next) {
	std::shared_ptr<TListItem> old = this->next;
	this->next = next;
	return old;
}

std::shared_ptr<Figure> TListItem::GetFigure() const {
	return this->figure;
}

std::shared_ptr<TListItem> TListItem::GetNext() {
	return this->next;
}

TListItem::~TListItem() {
	//std::cout << "List item deleted" << std::endl;
}
