#include "Scene.h"

void Scene::addSphere(const Sphere &sphere) {
    spheres.push_back(sphere);
}

void Scene::addLight(const Light &light) {
    lights.push_back(light);
}

Vector3D Scene::calculateLighting(const Vector3D &point, const Vector3D &normal, const Vector3D &sphereColor) const {
    Vector3D totalLight(0, 0, 0);

    for (const auto &light : lights) {
        Vector3D lightDir = (light.position - point).normalize();
        float intensity = std::max(lightDir.dot(normal), 0.0f);
        totalLight = totalLight + light.color.multiply(sphereColor) * intensity; // Corrected line
    }

    return totalLight;
}

// Find the closest intersection of a ray with any sphere in the scene
bool Scene::closestIntersection(const Ray &ray, float &closest_t, Sphere &closest_sphere) const {
    closest_t = std::numeric_limits<float>::max();
    bool intersection_found = false;

    for (const auto &sphere : spheres) {
        float t0, t1;
        if (sphere.intersect(ray, t0, t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < closest_t) {
                closest_t = t0;
                closest_sphere = sphere;
                intersection_found = true;
            }
        }
    }

    return intersection_found;
}
