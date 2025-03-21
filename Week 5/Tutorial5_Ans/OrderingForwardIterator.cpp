
#include "OrderingForwardIterator.h"


void OrderingForwardIterator::setMapPosition() {

}

OrderingForwardIterator::OrderingForwardIterator(const DataWrapper* aCollection) noexcept :
	fIndex(),
	fMapPosition()
{
	setMapPosition();
}

const DataMap& OrderingForwardIterator::operator*() noexcept {
	return (*fCollection)[fMapPosition];
}

OrderingForwardIterator& OrderingForwardIterator::operator++() noexcept {
	fIndex++;
	setMapPosition();
	return *this;
}  // prefix
OrderingForwardIterator OrderingForwardIterator::operator++(int) noexcept {
	OrderingForwardIterator old = *this;
	++(*this);
	return old;
}  // postfix

bool OrderingForwardIterator::operator==(const OrderingForwardIterator& aOther) const noexcept {
	//comparing
	return fCollection == aOther.fCollection && fIndex == aOther.fIndex;
}
bool OrderingForwardIterator::operator!=(const OrderingForwardIterator& aOther) const noexcept {
	return !(*this == aOther);
}

OrderingForwardIterator OrderingForwardIterator::begin() const noexcept {
	OrderingForwardIterator result = *this;
	result.fIndex = 0;
	result.setMapPosition();
	return result;
}
OrderingForwardIterator OrderingForwardIterator::end() const noexcept {
	OrderingForwardIterator result = *this;
	result.fIndex = fCollection->size()-1;
	return result;

}