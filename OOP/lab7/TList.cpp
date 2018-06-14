#include "TList.h"

#define MAX_LENGTH 5

template <class T, class TT> TList<T, TT>::TList(): head(nullptr), size(0) {
    head = nullptr;
}

template <class T, class TT> void TList<T, TT>::RemoveByType(const int type) {
    auto tmp = head;
    while (tmp) {
            for (auto i : * this) {
                for(int j = 0; j < tmp->GetValue()->GetSize(); ++j) {
                    if(i->GetData()[j]->type() == type) {
                        i->pop(j);
                        --j;
                    }
                }
            }
    tmp = tmp->GetNext();
    }
}

template <class T, class TT>
void TList<T, TT>::Insert(std::shared_ptr<TT> &&value) {

    bool inserted = false;
    if (head != nullptr) {

        for (auto i : * this) {
            if (i->GetSize() < MAX_LENGTH) {
                i->push(value);
                std::cout << "List: Add Element in list:" << i->GetSize() << std::endl;
                inserted = true;
            }
        }
    }

    if (!inserted) {
        std::shared_ptr<T> tmp(new T);
        tmp->push(value);
        std::shared_ptr<TListItem<T>> item(new TListItem<T>(tmp));
        item->SetNext(head);
        head = item;
        ++size;
        std::cout << "List: New list element created" << std::endl;
    }
}

template <class T, class TT> size_t TList<T, TT>::Size() {
    size_t result = 0;

    for (auto a : * this) result++;

    return result;
}

template <class T, class TT> TIterator<TListItem<T>, T> TList<T, TT>::begin() const{
    return TIterator<TListItem<T>, T>(head);
}

template <class T, class TT> TIterator<TListItem<T>, T> TList<T, TT>::end() const{
    return TIterator<TListItem<T>, T>(nullptr);
}

template <class T, class TT> TList<T, TT>::~TList() {
    std::cout << "List: deleted" << std::endl;
}

template <class A, class AA>
std::ostream& operator<<(std::ostream& os, const TList<A, AA>& list) {
    std::cout << "List:" << std::endl;
    for(auto i:list) std::cout << *i << std::endl;
    return os;
}

template class TList<TArray<Figure>, Figure >;
template std::ostream & operator <<(std::ostream &os, const TList< TArray<Figure>, Figure > &stack);