#include <cmath>
#include <algorithm>

#include "Figures.h"

// Constructor
Sphere::Sphere()
        : center(Vector3D()), radius(1.0), color(Vector3D(1.0, 1.0, 1.0)), reflectivity(0.0), transparency(0.0), refractiveIndex(1.0) {}

// Constructor with parameters
Sphere::Sphere(const Vector3D &center, float radius, const Vector3D &color, float reflectivity, float transparency, float refractiveIndex)
        : center(center), radius(radius), color(color), reflectivity(reflectivity), transparency(transparency), refractiveIndex(refractiveIndex) {}

// Check if a ray intersects with the sphere
bool Sphere::intersect(const Ray &ray, float &t0, float &t1) const {
    Vector3D L = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * ray.direction.dot(L);
    float c = L.dot(L) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false; // no intersection

    // Calculate the two points of intersection
    float discr_sqrt = sqrt(discriminant);
    t0 = (-b - discr_sqrt) / (2 * a);
    t1 = (-b + discr_sqrt) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    return true;
}
