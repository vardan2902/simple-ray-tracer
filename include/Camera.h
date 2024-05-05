#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#include "Ray.h"

class Camera {
public:
    Vector3D position;
    Vector3D direction;
    Vector3D up;
    float fov;

    // Constructor
    Camera(const Vector3D &position, const Vector3D &direction, const Vector3D &up, float fov);

    // Generate a ray passing through a given pixel
    [[nodiscard]] Ray getRay(float x, float y, int screenWidth, int screenHeight) const;
};

#endif // CAMERA_H
