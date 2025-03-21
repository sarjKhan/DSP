
// COS30008, Final Exam, 2022

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;
    
    const TTree* fTTree;                // ternary tree
    TTreeStack fStack;                  // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;
       
    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);
           
        return old;
    }
       
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

private:
    
    // push subtree of aNode
    void push_subtrees(const TTree* aNode) {
        fStack.push(aNode);
    }

public:
    
	// iterator constructor
    TernaryTreePrefixIterator(const TTree* aTTree) : fTTree(aTTree) {
        if (!aTTree->empty()) {
            fStack.push(aTTree);
        }
    }

	// iterator dereference
    const T& operator*() const {
        return *(fStack.top());
    }

    // prefix increment
    Iterator& operator++() {
        TTree lNode = fStack.top();
        fStack.pop();
        if (!(lNode.getLeft().empty())) {
            fStack.push(lNode.getRight());
        }
        if (!(lNode.getMiddle().empty())) {
            fStack.push(const_cast<TTree>(lNode.getMiddle()));
        }
        if (!(lNode.getLeft().empty())) {
            fStack.push(const_cast<TTree>(lNode.getLeft()));
        }

        return *this;
    }

	// iterator equivalence
    bool operator==(const Iterator& aOtherIter) const {
        return (fTTree == aOtherIter.fTTree && fStack.size() == aOtherIter.fStack.size());
    }

	// auxiliaries
    Iterator begin() const {
        return Iterator(fTTree);
    }
    Iterator end() const {
        Iterator iter = *this;

        iter.fStack = std::stack<const TTreeNode>();

        return iter;
    }
};
