#include "TList.h"

template <class T>
TList<T>::TList() : head(nullptr) {
}

template <class T> void TList<T>::push(std::shared_ptr<T> &&item) {
	std::shared_ptr<TListItem < T >> other(new TListItem<T>(item));
	other->SetNext(head);
	head = other;
	_size++;

}

template <class T>
void TList<T>::AddFirst(std::shared_ptr<T> figure) {
	std::shared_ptr<TListItem<T>> tmp(new TListItem<T>(figure));
	tmp->SetNext(head);
	head = tmp;

	//std::cout << "Figure added." << std::endl;
}

template <class T>
void TList<T>::AddLast(std::shared_ptr<T> figure) {
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
}

template <class T> void TList<T>::Insert(size_t pos, std::shared_ptr<T> figure) {
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
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TList<T>& list) {

	std::shared_ptr<TListItem<T>> item = list.head;

	while (item != nullptr)
	{
		std::cout << "[ ";
		item->GetValue()->Print();
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

template <class T>
TIterator<TListItem<T>, T> TList<T>::begin()
{
	return TIterator<TListItem<T>, T>(head);
}

template <class T>
TIterator<TListItem<T>, T> TList<T>::end()
{
	return TIterator<TListItem<T>, T>(nullptr);
}

template <class T> std::shared_ptr<T> TList<T>::operator[](size_t i) {
	if (i > size() - 1) throw std::invalid_argument("index greater then list size");
	size_t j = 0;

	for (std::shared_ptr<T> a : *this) {
		if (j == i) return a;
		j++;
	}

	return std::shared_ptr<T>(nullptr);
}

template <class T> void TList<T>::sort() {
	if (size() > 1) {
		std::shared_ptr<T> middle = pop();
		TList<T> left, right;

		while (!Empty()) {
			std::shared_ptr<T> item = pop();
			if (*item < *middle) {
				left.push(std::move(item));
			}
			else {
				right.push(std::move(item));
			}
		}

		left.sort();
		right.sort();

		while (!left.Empty()) push(left.pop_last());
		push(std::move(middle));
		while (!right.Empty()) push(right.pop_last());

	}
}

template<class T > std::future<void> TList<T>::sort_in_background() {

	std::packaged_task<void(void) > task(std::bind(std::mem_fn(&TList<T>::sort_parallel), this));
	std::future<void> res(task.get_future());
	std::thread th(std::move(task));
	th.detach();
	return res;

	//return std::async(std::bind(std::mem_fn(&TList<T>::sort_parallel), this));
}

template <class T> void TList<T>::sort_parallel() {
	if (size() > 1) {
		std::shared_ptr<T> middle = pop_last();
		TList<T> left, right;

		while (!Empty()) {
			std::shared_ptr<T> item = pop_last();
			if (*item < *middle) {
				left.push(std::move(item));
			}
			else {
				right.push(std::move(item));
			}
		}

		std::future<void> left_res = left.sort_in_background();
		std::future<void> right_res = right.sort_in_background();


		left_res.get();


		while (!left.Empty()) push(left.pop_last());
		push(std::move(middle));

		right_res.get();
		while (!right.Empty()) push(right.pop_last());

	}
}

template <class T> std::shared_ptr<T> TList<T>::pop() {
	std::shared_ptr<T> result;
	if (head != nullptr) {
		result = head->GetValue();
		head = head->GetNext();
	}

	return result;
}

template <class T> std::shared_ptr<T> TList<T>::pop_last() {
	std::shared_ptr<T> result;

	if (head != nullptr) {
		std::shared_ptr<TListItem<T>> element = head;
		std::shared_ptr<TListItem<T>> prev = nullptr;

		while (element->GetNext() != nullptr) {
			prev = element;
			element = element->GetNext();
		}

		if (prev != nullptr) {
			prev->SetNext(nullptr);
			result = element->GetValue();

		}
		else {
			result = element->GetValue();
			head = nullptr;
		}
	}

	return result;
}

template <class T> size_t TList<T>::size() {

	int result = 0;
	for (auto i : *this) result++;
	return result;
}

template <class T> TList<T>::~TList() {
	//delete head;
}

#include "Figure.h"
template class TList<Figure>;
template std::ostream& operator<<(std::ostream& os, const TList<Figure>& List);