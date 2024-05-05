#include "Figures.h"

bool Triangle::intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &surfaceNormal) const {
    const float EPSILON = 1e-8;
    Vector3D edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = v1 - v0;
    edge2 = v2 - v0;
    h = ray.direction.cross(edge2);
    a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON) {
        return false;    // The ray is parallel to the triangle
    }

    f = 1.0f / a;
    s = ray.origin - v0;
    u = f * s.dot(h);

    if (u < 0.0 || u > 1.0) {
        return false;    // The intersection is outside of the triangle
    }

    q = s.cross(edge1);
    v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0) {
        return false;    // The intersection is outside of the triangle
    }

    // At this stage, we can compute t to find out where the intersection point is on the line
    t = f * edge2.dot(q);
    if (t > EPSILON) { // Ray intersection
        hitPoint = ray.pointAtParameter(t);
        surfaceNormal = edge1.cross(edge2).normalize(); // Compute the normal of the triangle
        return true;
    }

    // This means that there is a line intersection but not a ray intersection
    return false;
}
