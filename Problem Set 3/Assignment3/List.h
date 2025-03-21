
// COS30008, Problem Set 3, 2023

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class List
{
private:
    using Node = typename DoublyLinkedList<T>::Node;
    
    Node fHead;		// first element
    Node fTail;		// last element
    size_t fSize;	// number of elements
    
public:

    using Iterator = DoublyLinkedListIterator<T>;
    
    List() noexcept : 
        fHead(),
        fTail(),
        fSize(0)
    {}// default constructor

	// copy semantics
    List(const List& aOther) : 
        fHead(aOther.fHead),
        fTail(aOther.fTail),
        fSize(aOther.fSize)
    {}					// copy constructor
    List& operator=(const List& aOther) {
        
        if (this != aOther) {
            
            this->~List();

            new (this) List(aOther);
        }

        return *this;
    }// copy assignment

	// move semantics
    List(List&& aOther) noexcept : 
        List()
    {
        swap(aOther);
    }				// move constructor
    List& operator=(List&& aOther) noexcept {

        if (this != &aOther) {
            swap(aOther);
        }

        return *this;
    }// move assignment
    void swap(List& aOther) noexcept {
        std::swap(fHead, aOther.fHead);
        std::swap(fTail, aOther.fTail);
        std::swap(fSize, aOther.fSize);
    }// swap elements

	// basic operations
    size_t size() const noexcept {
        return fSize;
    }// list size
    
    template<typename U>
    void push_front(U&& aData) {
        Node aNode = DoublyLinkedList<T>::makeNode(aData);

        aNode->fNext = fHead;
        if (fHead != nullptr) fHead->fPrevious = aNode;

        fHead = aNode;

        if (fTail == nullptr) fTail = fHead;
        fSize++;
    }// add element at front
    
    template<typename U>
    void push_back(U&& aData) {
        Node aNode = DoublyLinkedList<T>::makeNode(aData);

        aNode->fPrevious = fTail;
        if (fTail != nullptr) fTail->fNext = aNode;

        fTail = aNode;
        if (fHead == nullptr) fHead = fTail;
        fSize++;
    }// add element at back
    
    void remove(const T& aElement) noexcept {
        Node remove = fHead;
        while (remove->fData != aElement && remove != nullptr) {
            remove = remove->fNext;
        }
        if (remove->fData == aElement) {
            (remove)->isolate();
        }
        fSize--;
    }// remove element
    
    const T& operator[](size_t aIndex) const {
        assert(aIndex < fSize);

        Node result = fHead;

        for (size_t i = 1; i <= aIndex; i++) {
            result = result->fNext;
        }

        return result->fData;
    }// list indexer
    
	// iterator interface
    Iterator begin() const noexcept {
        Iterator aBegin = Iterator(fHead, fTail);

        return aBegin.begin();
    }
    Iterator end() const noexcept {
        Iterator aEnd = Iterator(fHead, fTail);

        return aEnd.end();
    }
    Iterator rbegin() const noexcept {
        Iterator aRBegin = Iterator(fHead, fTail);

        return aRBegin.rbegin();
    }
    Iterator rend() const noexcept {
        Iterator aREnd = Iterator(fHead, fTail);
        
        return aREnd.rend();
    }
};
