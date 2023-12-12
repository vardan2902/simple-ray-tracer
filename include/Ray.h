#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

class Ray {
public:
    Vector3D origin;
    Vector3D direction;

    // Constructors
    Ray();
    Ray(const Vector3D &origin, const Vector3D &direction);

    // Method to get a point along the ray at a specific t value
    Vector3D pointAtParameter(float t) const;
};

#endif // RAY_H
