#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"

class Light {
public:
    Vector3D position; // Position of the light
    Vector3D color;    // Color of the light

    // Constructor
    Light(const Vector3D &position, const Vector3D &color);
};

#endif // LIGHT_H
