#include <algorithm>

#include "Vector3D.h"
#include "Lights.h"
#include "utils.h"
#include "constants.h"
#include "Scene.h"

Vector3D DirectionalLight::jitterDirection(const Vector3D &lightDir, float jitterAmount) const {
    // Improved jittering: Generate a random vector on a hemisphere around the light direction
    // This requires a more sophisticated random vector generation method.
    // Assuming you have a function randomHemisphereVector(lightDir) that generates such a vector.

    Vector3D randomVector = randomHemisphereVector(lightDir) * jitterAmount;
    Vector3D jittered = lightDir + randomVector;
    jittered.normalize();
    return jittered;
}

float DirectionalLight::calculateSoftShadow(const Vector3D &lightDir, Vector3D &hitPoint, Vector3D &normal, const Scene *scene, float jitterAmount) const {
    int numSamples = 100;  // Number of shadow rays for soft shadows
    int unblockedRays = 0;

    for (int i = 0; i < numSamples; ++i) {
        Vector3D jitteredDirection = jitterDirection(lightDir, jitterAmount);
        Ray shadowRay(hitPoint + normal * BIAS, jitteredDirection);

        if (!scene->isInShadow(shadowRay, std::numeric_limits<float>::infinity(), hitPoint, normal))
            unblockedRays++;
    }

    return static_cast<float>(unblockedRays) / static_cast<float>(numSamples); // Fraction of rays not blocked
}

Vector3D DirectionalLight::calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const {
    Vector3D lightDir = -direction.normalize();  // Light direction is normalized and negated

    // Calculate the soft shadow factor
    float shadowFraction = calculateSoftShadow(lightDir, hitPoint, normal, scene, 0.5f);

    // Diffuse component
    float diffIntensity = std::max(lightDir.dot(normal), 0.0f);
    Vector3D diffuse = diffIntensity * color * intensity;

    // Specular component
    Vector3D reflectDir = reflect(-lightDir, normal).normalize();
    float specIntensity = std::pow(std::max(reflectDir.dot(viewDir), 0.0f), scene->shininess);
    Vector3D specular = specIntensity * color * intensity;

    // Apply the soft shadow factor to both diffuse and specular components
    Vector3D litColor = diffuse + specular;
    Vector3D shadowedColor(0, 0, 0); // Color when in shadow
    Vector3D finalColor = litColor * shadowFraction + shadowedColor * (1.0f - shadowFraction);

    return finalColor;
}
