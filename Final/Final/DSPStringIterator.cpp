
// COS30008, Final Exam, 2023

#include "DSPStringIterator.h"

DSPStringIterator::DSPStringIterator( const DSPString& aCollection ) :
	fCollection( std::make_shared<DSPString>( aCollection ) ),
	fIndex( 0 )
{}

char DSPStringIterator::operator*() const noexcept
{
	return (*fCollection.get())[fIndex];
}

DSPStringIterator& DSPStringIterator::operator++() noexcept
{
	fIndex++;
	return *this;
}

DSPStringIterator DSPStringIterator::operator++( int ) noexcept
{
	DSPStringIterator old = *this;

	++(*this);

	return old;
}

DSPStringIterator& DSPStringIterator::operator--() noexcept
{
	fIndex--;
	return *this;
}

DSPStringIterator DSPStringIterator::operator--( int ) noexcept
{
	DSPStringIterator old = *this;

	--(*this);

	return old;
}

bool DSPStringIterator::operator==( const DSPStringIterator& aOther ) const noexcept
{
	return fIndex == aOther.fIndex && fCollection == aOther.fCollection;
}

bool DSPStringIterator::operator!=( const DSPStringIterator& aOther ) const noexcept
{
	return !(*this == aOther);
}

DSPStringIterator  DSPStringIterator::begin() const noexcept
{
	DSPStringIterator begin = *this;
	begin.fIndex = 0;
	return begin;
}

DSPStringIterator DSPStringIterator::end() const noexcept
{
	DSPStringIterator end = *this;
	end.fIndex = fCollection.get()->size()-1;
	return end;
}

DSPStringIterator DSPStringIterator::rbegin() const noexcept
{
	DSPStringIterator rBegin = *this;
	return rBegin.end();
}

DSPStringIterator DSPStringIterator::rend() const noexcept
{
	DSPStringIterator rEnd = *this;
	rEnd.fIndex = -1;
	return rEnd;
}
