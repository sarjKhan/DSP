
// COS30008, Tutorial 7, 2023

#pragma once

#include "BaseSorter.h"

template<typename T>
class BubbleSorter : public BaseSorter<T>
{
public:
    
    BubbleSorter(T* aCollection = nullptr, size_t aSize = 0) :
        BaseSorter<T>(aCollection, aSize)
    {}
        
    template<typename C = std::greater<T>>
    void operator()(bool aPrintStage = true, C aIsOutOfOrder = C{}) noexcept {
        for (size_t i = 0; i < this->size() - 1; i++) {

            for (size_t j = 0; j < this->size() - i - 1; j++) {

                if (aIsOutOfOrder((*this)[j], (*this)[j + 1])) {
                    this->swap(j, j + 1);
                }
            }
            if (aPrintStage) this->printStage(2);
        }
    }
};
