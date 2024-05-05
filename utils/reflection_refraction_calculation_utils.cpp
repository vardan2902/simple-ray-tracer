#include "utils.h"
#include <iostream>

Vector3D reflect(const Vector3D &incident, const Vector3D &normal) {
    return incident - normal * 2 * incident.dot(normal);
}

Vector3D refract(const Vector3D &incident, const Vector3D &normal, float refractiveIndex) {
    float cosi = -std::max(-1.0f, std::min(1.0f, incident.dot(normal)));
    float etai = 1, etat = refractiveIndex;
    Vector3D n = normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -normal;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vector3D(0, 0, 0) : (incident * eta + n * (eta * cosi - sqrtf(k))).normalize();
}

QColor blendColors(const QColor &reflectionColor, const QColor &refractionColor, const QColor &localColor,
                   float transparency, float refractiveIndex, float viewDotNormal) {
    // Calculate Fresnel term using Schlick's approximation
    float F0 = powf((1 - refractiveIndex) / (1 + refractiveIndex), 2);
    float fresnelReflectance = F0 + (1 - F0) * powf(1 - std::max(0.0f, std::min(1.0f, viewDotNormal)), 5);

    // Calculate transmittance
    float fresnelTransmittance = 1.0f - fresnelReflectance;

    // Apply gamma correction to each color component
    float r = gammaCorrectComponent(static_cast<float>(localColor.red()) / 255.0f) * (1.0f - fresnelReflectance) +
              gammaCorrectComponent(static_cast<float>(reflectionColor.red()) / 255.0f) * fresnelReflectance +
              gammaCorrectComponent(static_cast<float>(refractionColor.red()) / 255.0f) * transparency *
              fresnelTransmittance;
    float g = gammaCorrectComponent(static_cast<float>(localColor.green()) / 255.0f) * (1.0f - fresnelReflectance) +
              gammaCorrectComponent(static_cast<float>(reflectionColor.green()) / 255.0f) * fresnelReflectance +
              gammaCorrectComponent(static_cast<float>(refractionColor.green()) / 255.0f) * transparency *
              fresnelTransmittance;
    float b = gammaCorrectComponent(static_cast<float>(localColor.blue()) / 255.0f) * (1.0f - fresnelReflectance) +
              gammaCorrectComponent(static_cast<float>(reflectionColor.blue()) / 255.0f) * fresnelReflectance +
              gammaCorrectComponent(static_cast<float>(refractionColor.blue()) / 255.0f) * transparency *
              fresnelTransmittance;

    // Convert the final color back to 8-bit format
    return {
            std::min(255, static_cast<int>(r * 255)),
            std::min(255, static_cast<int>(g * 255)),
            std::min(255, static_cast<int>(b * 255))
    };
}

Vector3D randomHemisphereVector(const Vector3D &normal) {
    // Generate two random numbers
    float rand1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float rand2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    // Spherical coordinates
    float theta = 2.0f * M_PI * rand1;
    float phi = acos(2.0f * rand2 - 1.0f);

    // Convert to Cartesian coordinates
    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);

    // Create a vector from the calculated coordinates
    Vector3D randomVec(x, y, z);

    // Align this vector with the given normal (hemisphere orientation)
    // Requires constructing an orthonormal basis
    Vector3D basis1, basis2;
    if (fabs(normal.x) > fabs(normal.z)) {
        basis1 = Vector3D(-normal.y, normal.x, 0.0f).normalize();
    } else {
        basis1 = Vector3D(0.0f, -normal.z, normal.y).normalize();
    }
    basis2 = normal.cross(basis1);

    // Transform the random vector to align it with the normal
    Vector3D hemisphereVec =
            randomVec.x * basis1 +
            randomVec.y * basis2 +
            randomVec.z * normal;

    return hemisphereVec.normalize();
}

Vector3D generateRandomPointInSphere(float radius) {
    float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
    float phi = acos(2.0f * static_cast<float>(rand()) / RAND_MAX - 1.0f);
    float r = cbrt(static_cast<float>(rand()) / RAND_MAX) * radius;  // Cube root for uniform distribution

    return Vector3D(
            r * sin(phi) * cos(theta),
            r * sin(phi) * sin(theta),
            r * cos(phi)
    );
}
