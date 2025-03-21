
// COS30008, tutorial 3, 2023

#pragma once

#include "Vector3D.h"

class Matrix3x3
{
private:
    
    Vector3D fRows[3];

public:
    Matrix3x3() noexcept;
    Matrix3x3( const Vector3D& aRow1 = Vector3D(1.0f, 0.0f, 0.0f), const Vector3D& aRow2 = Vector3D(0.0f, 1.0f, 0.0f), const Vector3D& aRow3 = Vector3D(0.0f, 0.0f, 1.0f)) noexcept;

    Matrix3x3 operator*( const float aScalar ) const noexcept;
    Matrix3x3 operator+( const Matrix3x3& aOther  ) const noexcept;

    Vector3D operator*( const Vector3D& aVector ) const noexcept;
    
    static Matrix3x3 scale( const float aX = 1.0f, const float aY = 1.0f );
    static Matrix3x3 translate( const float aX = 0.0f, const float aY = 0.0f );
    static Matrix3x3 rotate( const float aAngleInDegree = 0.0f );
    
    const Vector3D row( size_t aRowIndex ) const;
    const Vector3D column( size_t aColumnIndex ) const;
};
