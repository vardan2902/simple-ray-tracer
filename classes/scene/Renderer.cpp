#include "Renderer.h"
#include "constants.h"
#include "utils.h"

Renderer::Renderer(const Scene &scene, int width, int height)
        : scene(scene), camera(scene.getCamera()), imageWidth(width), imageHeight(height) {}

QImage Renderer::renderScene() const {
    QImage image(imageWidth, imageHeight, QImage::Format_RGB32);
    const int numSamples = 1; // Number of samples per pixel, e.g., 4

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            int accumulatedRed = 0;
            int accumulatedGreen = 0;
            int accumulatedBlue = 0;

            for (int s = 0; s < numSamples; s++) {
                // Jitter the ray's position for supersampling
                float jitterX = ((float) rand() / RAND_MAX - 0.5f) / static_cast<float>(imageWidth);
                float jitterY = ((float) rand() / RAND_MAX - 0.5f) / static_cast<float>(imageHeight);
                Ray ray = camera.getRay(x + jitterX, y + jitterY, imageWidth, imageHeight);

                QColor color = traceRay(ray, 1);
                accumulatedRed += color.red();
                accumulatedGreen += color.green();
                accumulatedBlue += color.blue();
            }

            // Average the accumulated color components and assign it to the pixel
            QColor finalColor(
                    accumulatedRed / numSamples,
                    accumulatedGreen / numSamples,
                    accumulatedBlue / numSamples
            );
            image.setPixelColor(x, y, finalColor);
        }
    }

    return image;
}

QColor Renderer::traceRay(const Ray &ray, int depth) const {
    if (depth > MAX_DEPTH)
        return {Qt::black};

    float closest_t;
    Vector3D hitPoint, normal, color;
    MaterialProperties materialProps{};

    if (!scene.closestIntersection(ray, closest_t, hitPoint, normal, color, materialProps) ||
        closest_t == std::numeric_limits<float>::max()) {
        // No intersection, return background color
        return {Qt::black};
    }

    Vector3D viewDir = -ray.direction.normalize();

    Vector3D localColor = scene.calculateLighting(hitPoint, normal, color, viewDir);

    QColor reflectionColor(Qt::black), refractionColor(Qt::black);


    // Calculate reflection if the material is reflective
    if (materialProps.reflectivity > 0) {
        Vector3D reflectionDir = reflect(ray.direction, normal).normalize();
        Ray reflectionRay(hitPoint + normal * BIAS, reflectionDir);
        reflectionColor = traceRay(reflectionRay, depth + 1);
    }

    // Calculate refraction if the material is transparent
    if (materialProps.transparency > 0) {
        Vector3D refractionDir = refract(ray.direction, normal, materialProps.refractiveIndex).normalize();
        Ray refractionRay(hitPoint - normal * BIAS, refractionDir);
        refractionColor = traceRay(refractionRay, depth + 1);
    }

    // Blend the colors based on material properties
    float viewDotNormal = std::max(viewDir.dot(normal), 0.0f);
    return blendColors(
            reflectionColor,
            refractionColor,
            QColor(
                    static_cast<int>(localColor.x * 255),
                    static_cast<int>(localColor.y * 255),
                    static_cast<int>(localColor.z * 255)
            ),
            materialProps.transparency,
            materialProps.refractiveIndex,
            viewDotNormal
    );
}
