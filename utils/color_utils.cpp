#include "utils.h"

float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}

float gammaCorrectComponent(float linearValue) {
    const float gamma = 2.2f;
    return powf(std::max(0.0f, linearValue), 1.0f / gamma);
}

Vector3D sRGBToLinear(const Vector3D &color) {
    return {
            std::pow(color.x, 2.2f),
            std::pow(color.y, 2.2f),
            std::pow(color.z, 2.2f)
    };
}

Vector3D linearToSRGB(const Vector3D &color) {
    return {
            clamp(std::pow(color.x, 1.0f / 2.2f), 0, 1),
            clamp(std::pow(color.y, 1.0f / 2.2f), 0, 1),
            clamp(std::pow(color.z, 1.0f / 2.2f), 0, 1)
    };
}
