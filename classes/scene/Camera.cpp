#include <cmath>

#include "Camera.h"

// Constructor
Camera::Camera(const Vector3D &position, const Vector3D &direction, float fov)
        : position(position), direction(direction.normalize()), fov(fov) {}

// Generate a ray for a given pixel
Ray Camera::getRay(float x, float y, int screenWidth, int screenHeight) const {
    // Convert pixel position to normalized device coordinates [-1, 1]
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    float ndcX = (2.0f * x / static_cast<float>(screenWidth) - 1.0f) * aspectRatio;
    float ndcY = 1.0f - 2.0f * y / static_cast<float>(screenHeight);

    // Calculate ray direction based on FOV
    float scale = tan(fov * 0.5f * M_PI / 180.0f);
    Vector3D rayDirection = Vector3D(ndcX * scale, ndcY * scale, -1.0f).normalize();

    return Ray(position, rayDirection);
}
