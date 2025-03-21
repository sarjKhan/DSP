
// COS30008, Tutorial 7, 2023

#pragma once

#include "BaseSorter.h"

#include <cstdlib>
#include <ctime>

template<typename T>
class FisherAndYatesSorter : public BaseSorter<T>
{
private:
    
    void shuffle() noexcept {
        size_t n = this->size();
        while (n > 0) {
            size_t k = std::rand() % n;
            n--;
            this->swap(n, k);
        }
    }
	
    template<typename C>
    bool isSorted(C aIsOutOfOrder) const noexcept {
        for (size_t i = 0; i < this->size()-1; i++) {
            if (aIsOutOfOrder((*this)[i], (*this)[i + 1])) {
                return false;
            }
        }
        return true;
    }
    
public:
    
    FisherAndYatesSorter( T* aCollection = nullptr, size_t aSize = 0 ) :
        BaseSorter<T>(aCollection, aSize)
    {
        std::srand(static_cast<unsigned>(std::time(NULL)));
    }

        
    template<typename C = std::greater<T>>
    void operator()(bool aPrintStage = true, C aIsOutOfOrder = C{}) noexcept {
        bool lSorted = false;
        do {
            lSorted = isSorted(aIsOutOfOrder);
            if (!lSorted) this->shuffle();
            //if (aPrintStage) this->printStage();
        } while (!lSorted);
    }
};
