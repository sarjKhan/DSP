
// COS30008, Final Exam, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree
{
public:
    
    using TTree = TernaryTree<T>;
    using TSubTree = TTree*;

private:
    
    T fKey;
    TSubTree fSubTrees[3];

    // private default constructor used for declaration of NIL
    TernaryTree() :
        fKey(T())
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            fSubTrees[i] = &NIL;
        }
    }

public:

    using Iterator = TernaryTreePrefixIterator<T>;
        
    static TTree NIL;           // sentinel

    // getters for subtrees
    const TTree& getLeft() const { return *fSubTrees[0]; }
    const TTree& getMiddle() const { return *fSubTrees[1]; }
    const TTree& getRight() const { return *fSubTrees[2]; }

    // add a subtree
    void addLeft( const TTree& aTTree ) { addSubTree( 0, aTTree ); }
    void addMiddle( const TTree& aTTree ) { addSubTree( 1, aTTree ); }
    void addRight( const TTree& aTTree ) { addSubTree( 2, aTTree ); }
            
    // remove a subtree, may through a domain error
    const TTree& removeLeft() { return removeSubTree( 0 ); }
    const TTree& removeMiddle() { return removeSubTree( 1 ); }
    const TTree& removeRight() { return removeSubTree( 2 ); }

/////////////////////////////////////////////////////////////////////////
// Problem 1: TernaryTree Basic Infrastructure

private:

    // remove a subtree, may throw a domain error [22]
    const TTree& removeSubTree(size_t aSubtreeIndex) {
        if (aSubtreeIndex < 3) {
            if (!empty()) {
                if (!(fSubTrees[aSubtreeIndex]->empty())) {
                    const TTree& Result = *fSubTrees[aSubtreeIndex];
                    fSubTrees[aSubtreeIndex] = &NIL;
                    return Result;
                }
                else {
                    throw std::domain_error("Empty subtree");
                }
            }
            else {
                throw std::domain_error("Empty TTree");
            }
        }
        else {
            throw std::domain_error("Index too large");
        }
    }
    
    // add a subtree; must avoid memory leaks; may throw domain error [18]
    void addSubTree(size_t aSubtreeIndex, const TTree& aTTree) {
        if (!empty()) {
            if (aSubtreeIndex < 3) {
                if (fSubTrees[aSubtreeIndex]->empty()) {
                    fSubTrees[aSubtreeIndex] = const_cast<TTree*>(&aTTree);
                }
                else {
                    throw std::domain_error("Non empty subtree");
                }
            }
            else {
                throw std::domain_error("Illegal subtree index");
            }
        }
        else {
            throw std::domain_error("Empty TTree");
        }
    }
    
public:
    
    // TernaryTree l-value constructor [10]
    TernaryTree(const T& aKey) : fKey(aKey) {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }
    
    // destructor (free sub-trees, must not free empty trees) [14]
    ~TernaryTree() {
        if (!empty()) {
            for (size_t i = 0; i < 3; i++)
            {
                if (!(fSubTrees[i]->empty())) {
                    delete fSubTrees[i];
                }
            }
        }
    }
    
    // return key value, may throw domain_error if empty [2]
    const T& operator*() const {
        if (!empty()) {
            return fKey;
        }
        else {
            throw std::domain_error("trying to access &NIL");
        }
    }

    // returns true if this ternary tree is empty [4]
    bool empty() const {
        return (this == &NIL);
    }

    // returns true if this ternary tree is a leaf [10]
    bool leaf() const {
        for (int i = 0; i < 3; i++) {
            if (fSubTrees[i]->empty()) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    size_t height() const {
        if (!empty()) {
            
        }
        else {
            throw std::domain_error("Undefined Height");
        }
    }
    
/////////////////////////////////////////////////////////////////////////
// Problem 2: TernaryTree Copy Semantics
    
    // copy constructor, must not copy empty ternary tree
    TernaryTree(const TTree& aOtherTTree) {
        if (!aOtherTTree.empty()) {
            TernaryTree();
            *this = aOtherTTree;
        }
        else {
            throw std::domain_error("Copying of NIL detected");
        }
    }

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
    TTree& operator=(const TTree& aOtherTTree) {
        if (this != &aOtherTTree) {
            if (!aOtherTTree.empty()) {

                this->~TernaryTree();

                fKey = aOtherTTree.fKey;

                for (int i = 0; i < 3; i++) {
                    if (!aOtherTTree.fSubTrees[i]->empty()) {
                        fSubTrees[i] = aOtherTTree.fSubTrees[i]->clone();
                    }
                    else {
                        fSubTrees[i] = &NIL;
                    }
                }

            }
            else {
                throw std::domain_error("Copying of NIL detected");
            }
        }
        return *this;
    }
    
    // clone ternary tree, must not copy empty trees
    TSubTree clone() const {
        if (!empty()) {
            return new TTree(*this);
        }
        else {
            throw std::domain_error("Cloning of NIL detected");
        }
    }

/////////////////////////////////////////////////////////////////////////
// Problem 3: TernaryTree Move Semantics

    // TTree r-value constructor
    TernaryTree(T&& aKey) : fKey(std::move(aKey)) {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }

    // move constructor, must not copy empty ternary tree
    TernaryTree(TTree&& aOtherTTree) {
        TernaryTree();
        *this = std::move(aOtherTTree);
    }

    // move assignment operator, must not copy empty ternary tree
    TTree& operator=(TTree&& aOtherTTree) noexcept {
        if (this != &aOtherTTree) {
            if (!aOtherTTree.empty()) {

                this->~TernaryTree();

                fKey = std::move(aOtherTTree.fKey);

                for (int i = 0; i < 3; i++) {
                    if (!(aOtherTTree.fSubTrees[i]->empty())) {
                        fSubTrees[i] = std::move(aOtherTTree.fSubTrees[i]);
                    }
                    else {
                        fSubTrees[i] = &NIL;
                    }
                }

            }
            else {
                throw std::domain_error("Copying of NIL detected");
            }
        }
        return *this;
    }
    
/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

    // return ternary tree prefix iterator positioned at start
    Iterator begin() const {
        Iterator i();
        i.begin();
    }

    // return ternary prefix iterator positioned at end
    Iterator end() const {
        Iterator i();
        i.end();
    }
};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
