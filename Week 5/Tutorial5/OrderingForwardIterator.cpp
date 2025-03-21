

#include "OrderingForwardIterator.h"

#define Ordering OrderingForwardIterator

void Ordering::setMapPosition() {
	for (size_t i = 0; i < fCollection->size(); i++) {
		if ((*fCollection)[i].key() == fIndex) {
			fMapPosition = i;
			break;
		}
	}
}

Ordering::OrderingForwardIterator(const DataWrapper* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0)
{
	setMapPosition();
}

const DataMap& Ordering::operator*() noexcept {
	return (*fCollection)[fMapPosition];
}

Ordering& Ordering::operator++() noexcept {
	fIndex++; //increment index
	setMapPosition(); //set new mapPosition
	return *this;
}

Ordering Ordering::operator++(int) noexcept {
	Ordering result = *this;
	++(*this);
	return result;
}

bool Ordering::operator==(const Ordering& aOther) const noexcept {
	return fIndex == aOther.fIndex && fCollection == aOther.fCollection; //also need to check the elements of the collection are equal
}

bool Ordering::operator!=(const Ordering& aOther) const noexcept {
	return !(*this == aOther);
}

Ordering Ordering::begin() const noexcept {
	Ordering result = *this;
	result.fIndex = 0;
	result.setMapPosition();
	return result;
}

Ordering Ordering::end() const noexcept {
	Ordering result = *this;
	result.fIndex = (*fCollection).size() - 1;
	return result;
}
