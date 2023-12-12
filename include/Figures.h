#ifndef FIGURES_H
#define FIGURES_H

#include "Vector3D.h"
#include "Ray.h"

class Sphere {
public:
    Vector3D center;
    Vector3D color;
    float radius;
    float reflectivity;
    float transparency;
    float refractiveIndex;

    // Constructor
    Sphere();
    Sphere(const Vector3D &center, float radius, const Vector3D &color, float reflectivity = 0.0, float transparency = 0.0, float refractiveIndex = 1.0);

    // Method to check intersection with a ray
    bool intersect(const Ray &ray, float &t0, float &t1) const;
};

#endif // FIGURES_H
