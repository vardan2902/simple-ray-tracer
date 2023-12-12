#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Lights.h"
#include "Figures.h"

class Scene {
public:
    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    // Methods to add objects to the scene
    void addSphere(const Sphere &sphere);
    void addLight(const Light &light);

    // Method to check for the closest intersection with any sphere in the scene
    bool closestIntersection(const Ray &ray, float &closest_t, Sphere &closest_sphere) const;

    // Calculate lighting at a point
    Vector3D calculateLighting(const Vector3D &point, const Vector3D &normal, const Vector3D &sphereColor) const;
};

class SceneParser {
public:
    static Scene parseScene(const std::string &filename);
};

#endif // SCENE_H
