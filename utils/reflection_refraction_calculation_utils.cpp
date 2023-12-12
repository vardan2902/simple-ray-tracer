#include "utils.h"

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
    return k < 0 ? Vector3D(0, 0, 0) : incident * eta + n * (eta * cosi - sqrtf(k));
}

QColor blendColors(const QColor &reflectionColor, const QColor &refractionColor, const QColor &localColor, float reflectivity) {
    float r = localColor.red() * (1 - reflectivity) +
              reflectionColor.red() * reflectivity +
              refractionColor.red() * (1 - reflectivity);
    float g = localColor.green() * (1 - reflectivity) +
              reflectionColor.green() * reflectivity +
              refractionColor.green() * (1 - reflectivity);
    float b = localColor.blue() * (1 - reflectivity) +
              reflectionColor.blue() * reflectivity +
              refractionColor.blue() * (1 - reflectivity);
    return QColor(std::min(255, int(r)), std::min(255, int(g)), std::min(255, int(b)));
}