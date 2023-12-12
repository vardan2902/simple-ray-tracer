#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <algorithm>
#include <QColor>

#include "Vector3D.h"

Vector3D reflect(const Vector3D &incident, const Vector3D &normal);
Vector3D refract(const Vector3D &incident, const Vector3D &normal, float refractiveIndex);
QColor blendColors(const QColor &reflectionColor, const QColor &refractionColor, const QColor &localColor, float reflectivity);

#endif //RAYTRACER_UTILS_H
