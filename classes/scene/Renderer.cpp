#include "Renderer.h"
#include "constants.h"
#include "utils.h"

Renderer::Renderer(const Scene &scene, const Camera &camera, int width, int height)
        : scene(scene), camera(camera), imageWidth(width), imageHeight(height) {}

QImage Renderer::renderScene() const {
    QImage image(imageWidth, imageHeight, QImage::Format_RGB32);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            Ray ray = camera.getRay(x, y, imageWidth, imageHeight);
            QColor color = calculatePixelColor(ray, 1);
            image.setPixelColor(x, y, color);
        }
    }

    return image;
}

QColor Renderer::calculatePixelColor(const Ray &ray, int depth) const {
    if (depth > MAX_DEPTH)
        return QColor(Qt::black);

    float closest_t;
    Sphere closest_sphere;
    if (scene.closestIntersection(ray, closest_t, closest_sphere)) {
        Vector3D hitPoint = ray.pointAtParameter(closest_t);
        Vector3D normal = (hitPoint - closest_sphere.center).normalize();
        Vector3D diffuseLight = scene.calculateLighting(hitPoint, normal, closest_sphere.color);

        // Initialize colors
        QColor reflectionColor(Qt::black), refractionColor(Qt::black);

        // Reflection
        if (closest_sphere.reflectivity > 0) {
            Vector3D reflectionDir = reflect(ray.direction, normal);
            Ray reflectionRay(hitPoint, reflectionDir);
            reflectionColor = calculatePixelColor(reflectionRay, depth + 1);
        }

        // Refraction
        if (closest_sphere.transparency > 0) {
            Vector3D refractionDir = refract(ray.direction, normal, closest_sphere.refractiveIndex);
            Ray refractionRay(hitPoint, refractionDir);
            refractionColor = calculatePixelColor(refractionRay, depth + 1);
        }

        // Blend the colors
        QColor localColor(diffuseLight.x * 255, diffuseLight.y * 255, diffuseLight.z * 255);
        return blendColors(reflectionColor, refractionColor, localColor, closest_sphere.reflectivity);
    }
    return QColor(Qt::black);
}
