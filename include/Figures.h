#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>

#include "Vector3D.h"
#include "Ray.h"
#include "SceneObject.h"

class Figure : public SceneObject {
public:
    // Material properties
    float reflectivity;
    float transparency;
    float refractiveIndex;
    Vector3D color;

    // Constructor
    Figure(float reflectivity, float transparency, float refractiveIndex, Vector3D color)
            : reflectivity(reflectivity), transparency(transparency), refractiveIndex(refractiveIndex), color(color) {}

    // Virtual method for intersection test
    virtual bool intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const = 0;
};

class Sphere : public Figure {
public:
    Vector3D center;
    Vector3D color;
    float radius;

    // Constructor
    Sphere();
    Sphere(
            const Vector3D &center,
            float radius,
            const Vector3D &color,
            float reflectivity,
            float transparency,
            float refractiveIndex
    ) : Figure(reflectivity, transparency, refractiveIndex, color), center(center), radius(radius) {}

    bool intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const override;
};

class Plane : public Figure {
public:
    Vector3D point;
    Vector3D normal;
    Vector3D color;

    Plane(
            const Vector3D &point,
            const Vector3D &normal,
            const Vector3D &color,
            float reflectivity,
            float transparency,
            float refractiveIndex
    ) : Figure(reflectivity, transparency, refractiveIndex, color), point(point), normal(normal), color(color) {}

    bool intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const override;
};

class Triangle : public Figure {
public:
    Vector3D v0, v1, v2;

    Triangle(
            const Vector3D &v0,
            const Vector3D &v1,
            const Vector3D &v2,
            const Vector3D &color,
            float reflectivity,
            float transparency,
            float refractiveIndex
    ) : Figure(reflectivity, transparency, refractiveIndex, color), v0(v0), v1(v1), v2(v2) {}

    bool intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const override;
};

class Mesh : public Figure {
public:
    std::vector<Triangle> triangles;

    Mesh(
            const std::vector<Triangle> &triangles,
            const Vector3D &color,
            float reflectivity,
            float transparency,
            float refractiveIndex
    ) : triangles(triangles), Figure(reflectivity, transparency, refractiveIndex, color) {}

    bool intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &normal) const override;
};

struct MaterialProperties {
    float reflectivity;
    float transparency;
    float refractiveIndex;
};

#endif // FIGURES_H
