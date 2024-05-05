#include <cmath>

#include "Figures.h"

bool Plane::intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &surfaceNormal) const {
    // Calculate denominator to check if ray is parallel to the plane
    float denom = normal.dot(ray.direction);
    if (std::fabs(denom) > 1e-6) { // Ensure the denominator is not too small, indicating the ray is not parallel to the plane
        Vector3D p0l0 = point - ray.origin;
        t = p0l0.dot(normal) / denom;
        if (t >= 0) { // Check if the intersection is in the direction of the ray
            hitPoint = ray.pointAtParameter(t); // Calculate the intersection point
            surfaceNormal = normal; // The normal at the intersection point is the same as the plane's normal
            return true;
        }
    }
    return false; // No intersection or ray is parallel to the plane
}