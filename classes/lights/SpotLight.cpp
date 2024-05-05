#include "Vector3D.h"
#include "Lights.h"
#include "Scene.h"
#include "utils.h"
#include "constants.h"

Vector3D SpotLight::calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir,
                                               const Scene *scene) const {
    Vector3D lightDir = (position - hitPoint).normalize();

    // Check if the point is within the spotlight cone
    float theta = std::acos(lightDir.dot(direction));
    if (theta > cutoffAngle)
        return {0, 0, 0};  // Outside the spotlight cone

    // Calculate the spotlight intensity
    float epsilon = falloff * (theta / cutoffAngle);
    float spotIntensity = pow(std::max(0.0f, 1 - epsilon), falloff);

    // Check if the point is in shadow
    Ray shadowRay(hitPoint + normal * BIAS, lightDir); // Offset the ray origin slightly to avoid self-intersection
    if (scene->isInShadow(shadowRay, std::numeric_limits<float>::infinity(), hitPoint, normal)) {
        return {0, 0, 0};  // No contribution if the point is in shadow
    }

    // Diffuse component
    float diff = std::max(normal.dot(lightDir), 0.0f);
    Vector3D diffuse = diff * color * intensity;

    // Specular component
    Vector3D reflectDir = reflect(-lightDir, normal).normalize();
    float spec = std::pow(std::max(viewDir.dot(reflectDir), 0.0f), scene->shininess); // Assuming shininess is a property of the scene or material
    Vector3D specular = spec * color * intensity;

    // Combine diffuse and specular components, considering the spotlight intensity
    return (diffuse + specular) * spotIntensity;
}