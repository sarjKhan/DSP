 
// Sartaj Khan Problem Set 1 Part 2
#include "Polygon.h"

#include <cassert>



float Polygon::getSignedArea() const noexcept {
    float aArea = 0;
    for (size_t i = 0; i < fNumberOfVertices - 1; i++) {
        aArea += 0.5f * (fVertices[i].y() + fVertices[i + 1].y()) * (fVertices[i].x() - fVertices[i + 1].x());
    }
    aArea += 0.5f * (fVertices[fNumberOfVertices - 1].y() + fVertices[0].y()) * (fVertices[fNumberOfVertices - 1].x() - fVertices[0].x());
    return aArea;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    
    Polygon Result = *this;
    for (size_t i = 0; i < fNumberOfVertices; i++) {
        Result.fVertices[i] = static_cast<Vector2D>(aMatrix * Vector3D(Result.fVertices[i]));
    }
    return Result;
}
