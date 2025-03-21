

#include "CharacterCounter.h"


CharacterCounter::CharacterCounter() noexcept :
	fTotalNumberOfCharacters(0)
{}


void CharacterCounter::count(unsigned char aCharacter) noexcept {
	fCharacterCounts[aCharacter].setCharacter(aCharacter);
	fCharacterCounts[aCharacter].increment();
	fTotalNumberOfCharacters++;
}

const CharacterMap& CharacterCounter::operator[] (unsigned char aCharacter) const noexcept {
	return fCharacterCounts[aCharacter];
}
