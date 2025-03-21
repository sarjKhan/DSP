
// COS30008, Final Exam, 2023

#include "DSPString.h"

#include <cassert>
#include <algorithm>

DSPString::DSPString( const char* aContents )
{
	size_t lSize = 0;

	while ( aContents[lSize] )
	{
		lSize++;
	}

	fContents = new char[++lSize];

	for ( size_t i = 0; i < lSize; i++ )
	{
		fContents[i] = aContents[i];
	}
	fSize = lSize;
}

DSPString::~DSPString()
{
	delete[] fContents;

}

DSPString::DSPString( const DSPString& aOther ) :
	DSPString( aOther.fContents )
{}

DSPString& DSPString::operator=( const DSPString& aOther )
{
	if (!(*this == aOther)) {
		this->~DSPString();

		new (this) DSPString(aOther.fContents);
	}

	return *this;

}

DSPString::DSPString( DSPString&& aOther ) noexcept :
	DSPString( "\0" )
{
	std::swap(fContents, aOther.fContents);
	std::swap(fSize, aOther.fSize);
}

DSPString& DSPString::operator=( DSPString&& aOther ) noexcept
{
	if (!(this == &aOther)) {
		std::swap(fContents, aOther.fContents);
		std::swap(fSize, aOther.fSize);
	}
	return *this;
}

size_t DSPString::size() const noexcept
{
	return fSize;

}

char DSPString::operator[]( size_t aIndex ) const noexcept
{
	assert(aIndex < fSize);
	return fContents[aIndex];
}

bool DSPString::operator==( const DSPString& aOther ) const noexcept
{
	if ( size() == aOther.size() )
	{
		for ( size_t i = 0; i < size(); i++ )
		{
			if ( fContents[i] != aOther.fContents[i] )
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

std::ostream& operator<<( std::ostream& aOStream, const DSPString& aObject )
{
	return aOStream << aObject.fContents;
}
