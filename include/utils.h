#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <algorithm>
#include <QColor>

#include "Vector3D.h"

float clamp(float value, float min, float max);
float gammaCorrectComponent(float linearValue);

Vector3D reflect(const Vector3D &incident, const Vector3D &normal);
Vector3D refract(const Vector3D &incident, const Vector3D &normal, float refractiveIndex);
QColor blendColors(const QColor &reflectionColor, const QColor &refractionColor, const QColor &localColor,
                   float transparency, float refractiveIndex, float viewDotNormal);
Vector3D linearToSRGB(const Vector3D &color);
Vector3D sRGBToLinear(const Vector3D &color);
Vector3D randomHemisphereVector(const Vector3D &normal);
Vector3D generateRandomPointInSphere(float radius);

#endif //RAYTRACER_UTILS_H
