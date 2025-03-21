
//Sartaj Khan - week 05

#include "SimpleForwardIterator.h"


#define Simple SimpleForwardIterator


Simple::SimpleForwardIterator(const DataWrapper* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0)
{}

const DataMap& Simple::operator*() noexcept {
	return (*fCollection)[fIndex];
}

Simple& Simple::operator++() noexcept {
	fIndex++;
	return *this;
}

Simple Simple::operator++(int) noexcept {
	Simple old = *this;
	++(*this);
	return old;
}

bool Simple::operator==(const Simple& aOther) const noexcept {
	return fIndex == aOther.fIndex && fCollection == aOther.fCollection; //also need to check the elements in fCollection are equal
}

bool Simple::operator!=(const Simple& aOther) const noexcept {
	return !(*this == aOther);
}

Simple Simple::begin() const noexcept {
	Simple result = *this;
	result.fIndex = 0;
	return result;
}

Simple Simple::end() const noexcept {
	Simple result = *this;
	result.fIndex = fCollection->size() - 1;
	return result;
}