
// COS30008, Tutorial 10, 2023

#pragma once

#include <memory>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:

    using Node = std::shared_ptr<DoublyLinkedList<T>>;
    using Next = std::shared_ptr<DoublyLinkedList<T>>;
    using Previous = std::weak_ptr<DoublyLinkedList<T>>;

    T fData;
    Next fNext;
    Previous fPrevious;

    // factory method for list nodes
    template<typename... Args>
    static Node makeNode(Args&&... args) {

        return std::make_shared<DoublyLinkedList>(std::forward<Args>(args)...);
    }
    
    DoublyLinkedList(const T& aData) noexcept :
        fData(aData),
        fNext(),
        fPrevious()
    {}
    
    DoublyLinkedList(T&& aData) noexcept :
        fData(std::move(aData)),
        fNext(),
        fPrevious()
    {}
    
    void isolate() noexcept {
        if (fNext) {
            fNext->fPrevious = fPrevious;
        }

        Node fNode = fPrevious.lock();

        if (fNode) {
            fNode->fNext = fNext;
        }

        fPrevious.reset();
        fNext.reset();
    }

    void swap(DoublyLinkedList& aOther) noexcept {
        std::swap(fData, aOther.fData);
        //std::swap(fNext, aOther.fNext);
        //std::swap(fPrevious, aOther.fPrevious);
    }
};
