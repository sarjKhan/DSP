
// COS30008, Tutorial 10, 2023

#pragma once

#include <cassert>
#include <stdexcept>

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
public:
    using Iterator = DoublyLinkedListIterator<T>;
    using Node = typename DoublyLinkedList<T>::Node;

    enum class States
    {
        BEFORE,
        DATA,
        AFTER
    };
    
    DoublyLinkedListIterator( const Node& aHead, const Node& aTail ) noexcept :
        fHead(aHead),
        fTail(aTail),
        fCurrent(aHead),
        fState(States::DATA)
    {
        assert(!fHead == !fTail);

        if (!fHead) {
            fState = States::AFTER;
        }
    }
    
    const T& operator*() const noexcept {
        return fCurrent->fData;
    }
    
    Iterator& operator++() noexcept {
        switch (fState)
        {
            case States::BEFORE:
                fCurrent = fHead;

                if (fCurrent)
                {
                    fState = States::DATA;
                }
                else
                {
                    fState = States::AFTER;
                }

                break;

            case States::DATA:
                fCurrent = fCurrent->fNext;

                if (!fCurrent)
                {
                    fState = States::AFTER;
                }

                break;

            case States::AFTER:
                break;
        }
        return *this;
    }// prefix
    Iterator operator++(int) noexcept {
        Iterator old = *this;
        ++(*this);
        return old;
    }// postfix
    
    Iterator& operator--() noexcept {
        switch (fState)
        {
            case States::BEFORE:

                break;

            case States::DATA:
                fCurrent = fCurrent->fPrevious.lock();

                if (!fCurrent)
                {
                    fState = States::BEFORE;
                }

                break;

            case States::AFTER:
                fCurrent = fTail;

                if (fCurrent)
                {
                    fState = States::DATA;
                }
                else
                {
                    fState = States::BEFORE;
                }

                break;
        }
        return *this;
    }// prefix
    Iterator operator--(int) noexcept {
        Iterator old = *this;
        --(*this);
        return old;
    }// postfix

    bool operator==(const Iterator& aOther) const noexcept {
        return fCurrent == aOther.fCurrent && fState == aOther.fState && fHead == aOther.fHead && fTail == aOther.fTail;
    }
    bool operator!=(const Iterator& aOther) const noexcept {
        return !(*this == aOther);
    }
    
    Iterator begin() const noexcept {
        return ++(rend());
    }
    Iterator end() const noexcept {
        Iterator end = *this;
        end.fCurrent = nullptr;
        end.fState = States::AFTER;

        return end;
    }
    Iterator rbegin() const noexcept {
        return --(end());
    }
    Iterator rend() const noexcept {
        Iterator rend = *this;

        rend.fCurrent = nullptr;
        rend.fState = States::BEFORE;

        return rend;
    }

private:
    Node fHead;
    Node fTail;
    Node fCurrent;
    States fState;
};
