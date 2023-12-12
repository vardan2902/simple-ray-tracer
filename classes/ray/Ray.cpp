#include "Ray.h"

// Default constructor
Ray::Ray() : origin(Vector3D()), direction(Vector3D()) {}

// Constructor with parameters
Ray::Ray(const Vector3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {}

// Get a point along the ray
Vector3D Ray::pointAtParameter(float t) const {
    return origin + direction * t;
}
