#include "Vector3D.h"
#include "Lights.h"
#include "utils.h"
#include "Scene.h"
#include "constants.h"

float PointLight::calculateSoftShadow(Vector3D &hitPoint, Vector3D &normal, const Scene *scene) const {
    int numSamples = 30;  // Number of samples for soft shadows
    float shadowSoftness = 1.5f;  // Radius of the area to jitter within
    int unblockedRays = 0;

    for (int i = 0; i < numSamples; ++i) {
        Vector3D jitteredPosition = position + generateRandomPointInSphere(shadowSoftness);
        Vector3D lightDir = (jitteredPosition - hitPoint).normalize();
        Ray shadowRay(hitPoint + normal * BIAS, lightDir);

        if (!scene->isInShadow(shadowRay, std::numeric_limits<float>::infinity(), hitPoint, normal))
            unblockedRays++;
    }

    return static_cast<float>(unblockedRays) / static_cast<float>(numSamples);
}

Vector3D PointLight::calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const {
    // Calculate the vector from the hitPoint on the surface to the light source
    Vector3D lightDir = (position - hitPoint).normalize();

    // Calculate soft shadow factor
    float softShadowFactor = calculateSoftShadow(hitPoint, normal, scene);

    // If the soft shadow factor is very low, it implies the point is largely in shadow
    if (softShadowFactor < 0.1f) {  // Threshold can be adjusted
        return Vector3D(0, 0, 0);
    }

    // Diffuse component
    float diff = std::max(normal.dot(lightDir), 0.0f);
    Vector3D diffuse = diff * color * intensity;

    // Specular component
    Vector3D reflectDir = reflect(-lightDir, normal).normalize();
    float spec = std::pow(std::max(viewDir.dot(reflectDir), 0.0f), scene->shininess);
    Vector3D specular = spec * color * intensity;

    // Attenuation
    float distance = (position - hitPoint).length();
    float attenuation = 1.0f / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);

    // Combine diffuse and specular components, modulated by the soft shadow factor
    return (diffuse + specular) * attenuation * softShadowFactor;
}
