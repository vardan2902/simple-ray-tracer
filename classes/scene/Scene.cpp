#include "Scene.h"
#include "constants.h"
#include "utils.h"

void Scene::addFigure(const std::shared_ptr<Figure> &figure) {
    figures.push_back(figure);
}

void Scene::addLight(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}

void Scene::setCamera(const Camera &cam) {
    camera = cam;
}

Camera Scene::getCamera() const {
    return camera;
}

Scene::Scene() : camera(Vector3D(0, 0, -2), Vector3D(0, 0, -1), Vector3D(0, 1, 0), 90.0f) {}

bool
Scene::closestIntersection(const Ray &ray, float &closest_t, Vector3D &hitPoint, Vector3D &normal, Vector3D &color,
                           MaterialProperties &materialProps) const {
    closest_t = std::numeric_limits<float>::max();
    bool hit = false;

    // Check for intersection with all figures
    for (const auto &figure: figures) {
        float t;
        Vector3D tempHitPoint, tempNormal, tempColor;
        if (figure->intersect(ray, t, tempHitPoint, tempNormal) && t < closest_t) {
            closest_t = t;
            hitPoint = tempHitPoint;  // Update hitPoint with the closest intersection
            normal = tempNormal;      // Update normal with the closest intersection
            color = figure->color;    // Update color with the color of the closest intersecting figure
            materialProps.reflectivity = figure->reflectivity;
            materialProps.transparency = figure->transparency;
            materialProps.refractiveIndex = figure->refractiveIndex;
            hit = true;
        }
    }

    return hit;
}

Vector3D Scene::calculateLighting(Vector3D &hitPoint, Vector3D &normal, const Vector3D &surfaceColor,
                                  const Vector3D &viewDir) const {
    Vector3D totalLight(0, 0, 0);

    // Convert surface color to linear space
    Vector3D linearSurfaceColor = sRGBToLinear(surfaceColor);

    for (const auto &light : lights) {
        // Calculate the light contribution and convert it to linear space
        Vector3D lightContribution = light->calculateLightContribution(hitPoint, normal, viewDir, this);
        Vector3D linearLightContribution = sRGBToLinear(lightContribution);

        // Add a portion of the light color to the surface color
        Vector3D modifiedSurfaceColor = {
                linearSurfaceColor.x + 0.1f * linearLightContribution.x,
                linearSurfaceColor.y + 0.1f * linearLightContribution.y,
                linearSurfaceColor.z + 0.1f * linearLightContribution.z
        };

        // Combine the modified surface color with the light contribution
        totalLight = {
                totalLight.x + linearLightContribution.x * modifiedSurfaceColor.x,
                totalLight.y + linearLightContribution.y * modifiedSurfaceColor.y,
                totalLight.z + linearLightContribution.z * modifiedSurfaceColor.z
        };
    }

    // Convert the final color back to sRGB space
    totalLight = linearToSRGB(totalLight);

    return totalLight;
}

bool Scene::isInShadow(const Ray &shadowRay, float distanceToLight, Vector3D &hitPoint, Vector3D &normal) const {
    Ray biasedShadowRay = Ray(hitPoint + normal * BIAS, shadowRay.direction);

    // Check for intersection with any object in the scene
    for (const auto &figure: figures) {
        float tHit;
        if (figure->intersect(biasedShadowRay, tHit, hitPoint, normal) && tHit < distanceToLight)
            return true; // Intersection found before the light source
    }
    return false; // No intersection found, not in shadow
}