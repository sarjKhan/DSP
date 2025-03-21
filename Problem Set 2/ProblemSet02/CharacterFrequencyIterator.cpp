

#include "CharacterFrequencyIterator.h"
#include <algorithm>


void CharacterFrequencyIterator::mapIndices() noexcept {
	for (int i = 0; i < 256; i++) {
		fMappedIndices[i] = (*fCollection)[i].character();
	}
	size_t i = 1;

	while (i < 256)
	{
		size_t j = i;

		while (j > 0 && std::less<CharacterMap>{}((*fCollection)[fMappedIndices[j - 1]], (*fCollection)[fMappedIndices[j]]))
		{
			std::swap(fMappedIndices[j - 1], fMappedIndices[j]);
			j--;
		}

		i++;
	}
}


CharacterFrequencyIterator::CharacterFrequencyIterator(const CharacterCounter* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0)
{
	mapIndices();
}


const CharacterMap& CharacterFrequencyIterator::operator*() const noexcept {
	return (*fCollection)[fMappedIndices[fIndex]];
}

CharacterFrequencyIterator& CharacterFrequencyIterator::operator++() noexcept {
	fIndex++;
	CharacterFrequencyIterator result = *this;
	if ((*result).frequency() == 0) fIndex = 256;
	return result;
}

CharacterFrequencyIterator CharacterFrequencyIterator::operator++(int) noexcept {
	CharacterFrequencyIterator old = *this;
	++(*this);
	return old;
}

bool CharacterFrequencyIterator::operator==(const CharacterFrequencyIterator& aOther) const noexcept{
	return fIndex == aOther.fIndex && fCollection == aOther.fCollection;
}

bool CharacterFrequencyIterator::operator!=(const CharacterFrequencyIterator& aOther) const noexcept {
	return !(*this == aOther);
}

CharacterFrequencyIterator CharacterFrequencyIterator::begin() const noexcept {
	CharacterFrequencyIterator result = *this;
	result.fIndex = 0;
	return result;
}

CharacterFrequencyIterator CharacterFrequencyIterator::end() const noexcept {
	CharacterFrequencyIterator result = *this;
	result.fIndex = 256; 
	return result;
}
