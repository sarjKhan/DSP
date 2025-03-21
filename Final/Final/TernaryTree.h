
// COS30008, Final Exam, 2023

#pragma once

#include <memory>
#include <cassert>
#include <algorithm>

template<typename T>
class TernaryTree
{
public:
    
    using Node = std::unique_ptr<TernaryTree>;

public:

    TernaryTree(const T& aKey = T{}) noexcept : fKey(aKey)
    
    {
        for (size_t i = 0; i < 3; i++) {
            fNodes[i] = nullptr;
        }
    }
    TernaryTree(T&& aKey) noexcept : fKey(std::move(aKey)) 
    {
        for (size_t i = 0; i < 3; i++) {
            fNodes[i] = nullptr;
        }
    }

    template<typename... Args>
    static Node makeNode(Args&&... args) {
        return std::make_unique<TernaryTree>(std::forward<Args>(args)...);
    }

    const T& operator*() const noexcept {
        return fKey;
    }

    TernaryTree& operator[](size_t aIndex) const {
        assert(aIndex < 3);
        return *fNodes[aIndex];
    }

    void add(size_t aIndex, Node& aNode) {
        assert(aIndex < 3);
        if (this) {
            if (!fNodes[aIndex]) {
                fNodes[aIndex] = std::move(aNode);
            }
        }
    }
    Node remove(size_t aIndex) {
        assert(aIndex < 3);
        if (this) {
            if (fNodes[aIndex]) {
                Node lRemoved = std::move(fNodes[aIndex]);
                return lRemoved;
            }
        }
    }

    bool leaf() const noexcept {
        if (this) {
            for (size_t i = 0; i < 3; i++) {
                if (fNodes[i] == nullptr)  {
                    continue;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
    size_t height() const noexcept {
        if (leaf()) {
            return 0;
        }
        else {
            size_t lHeight = fNodes[0]->height();
            size_t mHeight = fNodes[1]->height();
            size_t rHeight = fNodes[2]->height();

            if (lHeight >= mHeight && lHeight >= rHeight) return lHeight+1;
            if (mHeight >= lHeight && mHeight >= rHeight) return mHeight+1;
            if (rHeight >= mHeight && rHeight >= lHeight) return rHeight+1;
        }
    }

private:

    T fKey;
    Node fNodes[3];
};

