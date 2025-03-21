
#define _USE_MATH_DEFINES
#include "Matrix3x3.h"

#include <cmath>
#include <cassert>

Matrix3x3::Matrix3x3() noexcept {
	fRows[0] = Vector3D(1.0f, 0.0f, 0.0f);
	fRows[1] = Vector3D(0.0f, 1.0f, 0.0f);
	fRows[2] = Vector3D(0.0f, 0.0f, 1.0f);
}

Matrix3x3::Matrix3x3(const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3) noexcept :
	fRows{ aRow1, aRow2, aRow3 }
{}

Matrix3x3 Matrix3x3::operator*(const float aScalar) const noexcept {
	return Matrix3x3(fRows[0] * aScalar, fRows[1] * aScalar, fRows[2] * aScalar);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 & aOther) const noexcept {
	return Matrix3x3(fRows[0] + aOther.row(0), fRows[1] + aOther.row(1), fRows[2] + aOther.row(2));
}


Vector3D Matrix3x3::operator*(const Vector3D& aVector) const noexcept {
	return Vector3D(fRows[0].dot(aVector), fRows[1].dot(aVector), fRows[2].dot(aVector));
}

Matrix3x3 Matrix3x3::scale(const float aX, const float aY) {
	Vector3D aRow1 = Vector3D(aX, 0.0f, 0.0f);
	Vector3D aRow2 = Vector3D(0.0f, aY, 0.0f);
	Vector3D aRow3 = Vector3D(0.0f, 0.0f, 1.0f);
	return Matrix3x3(aRow1, aRow2, aRow3);
}

Matrix3x3 Matrix3x3::translate(const float aX, const float aY) {
	Vector3D aRow1 = Vector3D(1.0f, 0.0f, aX);
	Vector3D aRow2 = Vector3D(0.0f, 1.0f, aY);
	Vector3D aRow3 = Vector3D(0.0f, 0.0f, 1.0f);
	return Matrix3x3(aRow1, aRow2, aRow3);
}

Matrix3x3 Matrix3x3::rotate(const float aAngleInDegree) {
	float aAngleInRadian = aAngleInDegree * (static_cast<float>(M_PI) / 180.0f);
	Vector3D aRow1 = Vector3D(std::cos(aAngleInRadian), -std::sin(aAngleInRadian), 0.0f);
	Vector3D aRow2 = Vector3D(std::sin(aAngleInRadian), std::cos(aAngleInRadian), 0.0f);
	Vector3D aRow3 = Vector3D(0.0f, 0.0f, 1.0f);
	return Matrix3x3(aRow1, aRow2, aRow3);
}

const Vector3D Matrix3x3::row(size_t aRowIndex) const {
	assert(aRowIndex < 3);
	return fRows[aRowIndex];
}

const Vector3D Matrix3x3::column(size_t aColumnIndex) const {
	assert(aColumnIndex < 3);
	return Vector3D(fRows[0][aColumnIndex], fRows[1][aColumnIndex], fRows[2][aColumnIndex]);
}

