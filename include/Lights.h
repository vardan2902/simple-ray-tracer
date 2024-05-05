#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"
#include "SceneObject.h"

class Scene;

class Light : public SceneObject {
public:
    Vector3D color;
    float intensity;

    Light(const Vector3D &color, float intensity)
            : color(color), intensity(intensity) {}

    virtual Vector3D calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const = 0;
};


class PointLight : public Light {
private:
    Vector3D position;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float calculateSoftShadow(Vector3D &hitPoint, Vector3D &normal, const Scene *scene) const;

public:
    PointLight(const Vector3D &position, const Vector3D &color, float intensity,
               float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
            : Light(color, intensity), position(position),
              constantAttenuation(constantAttenuation), linearAttenuation(linearAttenuation),
              quadraticAttenuation(quadraticAttenuation) {}

    Vector3D calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const override;
};

class DirectionalLight : public Light {
private:
    float calculateSoftShadow(const Vector3D &lightDir, Vector3D &hitPoint, Vector3D &normal, const Scene *scene, float jitterAmount) const;
public:
    Vector3D direction;

    DirectionalLight(const Vector3D &direction, const Vector3D &color, float intensity)
            : Light(color, intensity), direction(direction.normalize()) {}

    Vector3D calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const override;

    Vector3D jitterDirection(const Vector3D &lightDir, float jitterAmount) const;
};

class SpotLight : public Light {
    Vector3D position;
    Vector3D direction;  // The direction in which the spotlight is pointing
    float cutoffAngle;   // Angle for the spotlight's spread
    float falloff;       // Determines how light intensity decreases from the center to the edge of the spotlight

public:
    SpotLight(const Vector3D &position, const Vector3D &direction, float cutoffAngle, float falloff,
              const Vector3D &color, float intensity)
            : Light(color, intensity), position(position), direction(direction.normalize()),
              cutoffAngle(cutoffAngle), falloff(falloff) {}

    Vector3D calculateLightContribution(Vector3D &hitPoint, Vector3D &normal, const Vector3D &viewDir, const Scene *scene) const override;
};

#endif // LIGHT_H
