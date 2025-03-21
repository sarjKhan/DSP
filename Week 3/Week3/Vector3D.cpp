#include "Vector3D.h"

#include <cmath>
#include <cassert>

Vector3D::Vector3D(float aX, float aY, float aW) noexcept :
	fBaseVector(Vector2D(aX, aY)),
	fW(aW)
{}

Vector3D::Vector3D(const Vector2D aVector) noexcept :
	fBaseVector(aVector),
	fW(1.0f)
{}

float Vector3D::operator[] (size_t aIndex) const 
{
	assert(aIndex < 3);

	return *(reinterpret_cast<const float*>(this) + aIndex);
}

Vector3D::operator Vector2D() const noexcept {

	return Vector2D(fBaseVector.x() / fW, fBaseVector.y() / fW);
}

Vector3D Vector3D::operator*(const float aScalar) const noexcept {
	return Vector3D(fBaseVector.x() * aScalar, fBaseVector.y() * aScalar,fW * aScalar);
}

Vector3D Vector3D::operator+ (const Vector3D& aOther) const noexcept {
	return Vector3D(fBaseVector.x() + aOther.x(), fBaseVector.y() + aOther.y(), fW + aOther.w());
}

float Vector3D::dot(const Vector3D& aOther) const noexcept {
	return (fBaseVector.x() * aOther.x() + fBaseVector.y() * aOther.y() + fW * aOther.w());
}

std::ostream& operator<<(std::ostream& aOStream, const Vector3D& aVector) {
	Vector2D aOther = static_cast<Vector2D>(aVector);
	return aOStream << "[" << aOther.x() << "," << aOther.y() << "]";
}
