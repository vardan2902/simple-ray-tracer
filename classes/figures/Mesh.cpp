#include <vector>

#include "Figures.h"

bool Mesh::intersect(const Ray &ray, float &t, Vector3D &hitPoint, Vector3D &surfaceNormal) const {
    bool hasIntersection = false;
    float closestT = std::numeric_limits<float>::max();

    for (const auto& triangle : triangles) {
        float tTemp;
        Vector3D hitPointTemp, normalTemp;
        if (triangle.intersect(ray, tTemp, hitPointTemp, normalTemp)) {
            if (tTemp < closestT) {
                closestT = tTemp;
                hitPoint = hitPointTemp;
                surfaceNormal = normalTemp;
                hasIntersection = true;
            }
        }
    }

    if (hasIntersection) {
        t = closestT;
        return true;
    }

    return false;
}
