// Tut2 Reading input from file and drawing out a T-Rex

#include "Polygon.h"
#include <cassert>

Polygon::Polygon() noexcept :
	fNumberOfVertices(0)
{}


void Polygon::readData(std::istream& aIStream) 
{
	while (aIStream >> fVertices[fNumberOfVertices]) 
	{
		fNumberOfVertices++;
	}
}


size_t Polygon::getNumberOfVertices() const noexcept{
	return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const{
	assert(aIndex < fNumberOfVertices);
	return fVertices[aIndex];
}


float Polygon::getPerimeter() const noexcept {

	float result = 0.0f;
	if (fNumberOfVertices > 2) {
		for (size_t i = 1; i < fNumberOfVertices; i++) {
			result += (fVertices[i] - fVertices[i - 1]).length();
		}
	}
	result += (fVertices[0] - fVertices[fNumberOfVertices - 1]).length();
	return result;
}


Polygon Polygon::scale(float aScalar) const noexcept {

	Polygon Result = *this;
	for (size_t i = 0; i < fNumberOfVertices; i++) {
		Result.fVertices[i] = fVertices[i] * aScalar;
	}
	return Result;
}