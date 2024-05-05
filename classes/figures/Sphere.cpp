#include <cmath>
#include <algorithm>

#include "Figures.h"

// Constructor
Sphere::Sphere()
        : center(Vector3D()), radius(1.0), color(Vector3D(1.0, 1.0, 1.0)), Figure(1.0, 1.0, 1.0, Vector3D(1, 1, 1)) {}

// Check if a ray intersects with the sphere
bool Sphere::intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const {
    Vector3D oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;  // No intersection
    }

    float sqrtDiscriminant = sqrt(discriminant);
    float t0 = (-b - sqrtDiscriminant) / (2 * a);
    float t1 = (-b + sqrtDiscriminant) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;  // If t0 is negative, use t1 instead
        if (t0 < 0) return false;  // Both t0 and t1 are negative
    }

    t = t0;

    // Calculate hit point and normal at the intersection
    hitPoint = ray.pointAtParameter(t);
    normal = (hitPoint - center) / radius;  // Normalize the normal
    normal.normalize();  // Ensure normal is indeed normalized

    return true;
}
