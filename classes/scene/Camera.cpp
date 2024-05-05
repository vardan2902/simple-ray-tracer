#include <cmath>
#include <cstdio>

#include "Camera.h"

// Constructor
Camera::Camera(const Vector3D &position, const Vector3D &direction, const Vector3D &up, float fov)
        : position(position), direction(direction.normalize()), up(up.normalize()), fov(fov) {}

// Generate a ray for a given pixel
Ray Camera::getRay(float x, float y, int screenWidth, int screenHeight) const {
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    float ndcX = (2.0f * x / static_cast<float>(screenWidth) - 1.0f) * aspectRatio;
    float ndcY = 1.0f - 2.0f * y / static_cast<float>(screenHeight);

    auto scale = static_cast<float>(tan(fov * 0.5f * M_PI / 180.0f));
    Vector3D rayDirection = Vector3D(ndcX * scale, ndcY * scale, -1.0f).normalize(); // Camera space

    // Convert ray from camera space to world space
    Vector3D forward = direction;
    Vector3D right = up.cross(forward).normalize();
    Vector3D trueUp = forward.cross(right).normalize();

    Vector3D worldRayDirection =
            right * rayDirection.x +
            trueUp * rayDirection.y +
            forward * rayDirection.z;
    worldRayDirection = worldRayDirection.normalize();

    return {position, worldRayDirection};
}
